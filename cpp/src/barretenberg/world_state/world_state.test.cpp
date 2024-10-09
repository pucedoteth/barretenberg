#include "barretenberg/world_state/world_state.hpp"
#include "barretenberg/crypto/merkle_tree/fixtures.hpp"
#include "barretenberg/crypto/merkle_tree/indexed_tree/indexed_leaf.hpp"
#include "barretenberg/crypto/merkle_tree/response.hpp"
#include "barretenberg/ecc/curves/bn254/fr.hpp"
#include "barretenberg/vm/aztec_constants.hpp"
#include "barretenberg/world_state/fork.hpp"
#include "barretenberg/world_state/types.hpp"
#include <cstdint>
#include <filesystem>
#include <gtest/gtest.h>
#include <sys/types.h>
#include <unordered_map>

using namespace bb::world_state;
using namespace bb::crypto::merkle_tree;

class WorldStateTest : public testing::Test {
  protected:
    void SetUp() override
    {
        data_dir = random_temp_directory();
        std::filesystem::create_directories(data_dir);
    }

    void TearDown() override { std::filesystem::remove_all(data_dir); }

    static std::string data_dir;
    uint64_t map_size = 10240;
    uint64_t thread_pool_size = 1;
    std::unordered_map<MerkleTreeId, uint32_t> tree_heights{
        { MerkleTreeId::NULLIFIER_TREE, 20 },   { MerkleTreeId::NOTE_HASH_TREE, 32 },
        { MerkleTreeId::PUBLIC_DATA_TREE, 40 }, { MerkleTreeId::L1_TO_L2_MESSAGE_TREE, 16 },
        { MerkleTreeId::ARCHIVE, 16 },
    };
    std::unordered_map<MerkleTreeId, index_t> tree_prefill{
        { MerkleTreeId::NULLIFIER_TREE, 128 },
        { MerkleTreeId::PUBLIC_DATA_TREE, 128 },
    };
    uint32_t initial_header_generator_point = 28;
};

std::string WorldStateTest::data_dir;

template <typename Leaf>
void assert_leaf_status(
    const WorldState& ws, WorldStateRevision revision, MerkleTreeId tree_id, index_t leaf_index, bool exists)
{
    std::optional<Leaf> leaf = ws.get_leaf<Leaf>(revision, tree_id, leaf_index);
    EXPECT_EQ(leaf.has_value(), exists);
}

template <typename Leaf>
void assert_leaf_value(const WorldState& ws,
                       WorldStateRevision revision,
                       MerkleTreeId tree_id,
                       index_t leaf_index,
                       const Leaf& expected_value)
{
    std::optional<Leaf> leaf = ws.get_leaf<Leaf>(revision, tree_id, leaf_index);
    EXPECT_EQ(leaf.has_value(), true);
    EXPECT_EQ(leaf.value(), expected_value);
}

template <typename Leaf>
void assert_leaf_exists(
    const WorldState& ws, WorldStateRevision revision, MerkleTreeId tree_id, const Leaf& expected_value, bool exists)
{
    std::optional<index_t> index = ws.find_leaf_index(revision, tree_id, expected_value);
    EXPECT_EQ(index.has_value(), exists);
}

template <typename Leaf>
void assert_leaf_index(
    const WorldState& ws, WorldStateRevision revision, MerkleTreeId tree_id, const Leaf& value, index_t expected_index)
{
    std::optional<index_t> index = ws.find_leaf_index<Leaf>(revision, tree_id, value);
    EXPECT_EQ(index.value(), expected_index);
}

void assert_tree_size(const WorldState& ws, WorldStateRevision revision, MerkleTreeId tree_id, size_t expected_size)
{
    auto info = ws.get_tree_info(revision, tree_id);
    EXPECT_EQ(info.meta.size, expected_size);
}

void assert_sibling_path(
    const WorldState& ws, WorldStateRevision revision, MerkleTreeId tree_id, fr root, fr leaf, index_t index)
{
    auto sibling_path = ws.get_sibling_path(revision, tree_id, index);
    fr left;
    fr right;
    fr hash = leaf;
    for (const auto& node : sibling_path) {
        if (index % 2 == 0) {
            left = hash;
            right = node;
        } else {
            left = node;
            right = hash;
        }

        hash = HashPolicy::hash_pair(left, right);
        index >>= 1;
    }

    EXPECT_EQ(hash, root);
}

void assert_fork_state_unchanged(const WorldState& ws,
                                 Fork::Id forkId,
                                 bool includeUncommitted,
                                 const std::vector<MerkleTreeId>& trees = { MerkleTreeId::NULLIFIER_TREE,
                                                                            MerkleTreeId::NOTE_HASH_TREE,
                                                                            MerkleTreeId::PUBLIC_DATA_TREE,
                                                                            MerkleTreeId::L1_TO_L2_MESSAGE_TREE,
                                                                            MerkleTreeId::ARCHIVE })
{

    for (auto tree_id : trees) {
        auto canonical_tree_info =
            ws.get_tree_info(WorldStateRevision{ .includeUncommitted = includeUncommitted }, tree_id);
        auto fork_tree_info = ws.get_tree_info(
            WorldStateRevision{
                .forkId = forkId,
                .includeUncommitted = includeUncommitted,
            },
            tree_id);

        EXPECT_EQ(canonical_tree_info.meta, fork_tree_info.meta);
    }
}

TEST_F(WorldStateTest, GetInitialTreeInfoForAllTrees)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);

    {
        auto info = ws.get_tree_info(WorldStateRevision::committed(), MerkleTreeId::NULLIFIER_TREE);
        EXPECT_EQ(info.meta.size, 128);
        EXPECT_EQ(info.meta.depth, tree_heights.at(MerkleTreeId::NULLIFIER_TREE));
        EXPECT_EQ(info.meta.root, bb::fr("0x19a8c197c12bb33da6314c4ef4f8f6fcb9e25250c085df8672adf67c8f1e3dbc"));
    }

    {
        auto info = ws.get_tree_info(WorldStateRevision::committed(), MerkleTreeId::NOTE_HASH_TREE);
        EXPECT_EQ(info.meta.size, 0);
        EXPECT_EQ(info.meta.depth, tree_heights.at(MerkleTreeId::NOTE_HASH_TREE));
        EXPECT_EQ(info.meta.root, bb::fr("0x0b59baa35b9dc267744f0ccb4e3b0255c1fc512460d91130c6bc19fb2668568d"));
    }

    {
        auto info = ws.get_tree_info(WorldStateRevision::committed(), MerkleTreeId::PUBLIC_DATA_TREE);
        EXPECT_EQ(info.meta.size, 128);
        EXPECT_EQ(info.meta.depth, tree_heights.at(MerkleTreeId::PUBLIC_DATA_TREE));
        EXPECT_EQ(info.meta.root, bb::fr("0x23c08a6b1297210c5e24c76b9a936250a1ce2721576c26ea797c7ec35f9e46a9"));
    }

    {
        auto info = ws.get_tree_info(WorldStateRevision::committed(), MerkleTreeId::L1_TO_L2_MESSAGE_TREE);
        EXPECT_EQ(info.meta.size, 0);
        EXPECT_EQ(info.meta.depth, tree_heights.at(MerkleTreeId::L1_TO_L2_MESSAGE_TREE));
        EXPECT_EQ(info.meta.root, bb::fr("0x14f44d672eb357739e42463497f9fdac46623af863eea4d947ca00a497dcdeb3"));
    }

    {
        auto info = ws.get_tree_info(WorldStateRevision::committed(), MerkleTreeId::ARCHIVE);
        EXPECT_EQ(info.meta.size, 1);
        EXPECT_EQ(info.meta.depth, tree_heights.at(MerkleTreeId::ARCHIVE));
        // this is the expected archive tree root at genesis
        EXPECT_EQ(info.meta.root, bb::fr("0x1200a06aae1368abe36530b585bd7a4d2ba4de5037b82076412691a187d7621e"));
    }
}

TEST_F(WorldStateTest, GetStateReference)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);

    {
        auto state_ref = ws.get_state_reference(WorldStateRevision::committed());
        {
            auto snapshot = state_ref.at(MerkleTreeId::NULLIFIER_TREE);
            EXPECT_EQ(
                snapshot,
                std::make_pair(bb::fr("0x19a8c197c12bb33da6314c4ef4f8f6fcb9e25250c085df8672adf67c8f1e3dbc"), 128UL));
        }

        {
            auto snapshot = state_ref.at(MerkleTreeId::NOTE_HASH_TREE);
            EXPECT_EQ(
                snapshot,
                std::make_pair(bb::fr("0x0b59baa35b9dc267744f0ccb4e3b0255c1fc512460d91130c6bc19fb2668568d"), 0UL));
        }

        {
            auto snapshot = state_ref.at(MerkleTreeId::PUBLIC_DATA_TREE);
            EXPECT_EQ(
                snapshot,
                std::make_pair(bb::fr("0x23c08a6b1297210c5e24c76b9a936250a1ce2721576c26ea797c7ec35f9e46a9"), 128UL));
        }

        {
            auto snapshot = state_ref.at(MerkleTreeId::L1_TO_L2_MESSAGE_TREE);
            EXPECT_EQ(
                snapshot,
                std::make_pair(bb::fr("0x14f44d672eb357739e42463497f9fdac46623af863eea4d947ca00a497dcdeb3"), 0UL));
        }
    }

    {
        ws.append_leaves<bb::fr>(MerkleTreeId::NOTE_HASH_TREE, { 1 });

        auto state_ref = ws.get_state_reference(WorldStateRevision::uncommitted());
        {
            auto snapshot = state_ref.at(MerkleTreeId::NULLIFIER_TREE);
            EXPECT_EQ(
                snapshot,
                std::make_pair(bb::fr("0x19a8c197c12bb33da6314c4ef4f8f6fcb9e25250c085df8672adf67c8f1e3dbc"), 128UL));
        }

        {
            auto snapshot = state_ref.at(MerkleTreeId::NOTE_HASH_TREE);
            EXPECT_EQ(
                snapshot,
                std::make_pair(bb::fr("0x12dbc0ae893e0aa914df8ed20837148c89d78fbef9471ede1d39416d9660c169"), 1UL));
        }

        {
            auto snapshot = state_ref.at(MerkleTreeId::PUBLIC_DATA_TREE);
            EXPECT_EQ(
                snapshot,
                std::make_pair(bb::fr("0x23c08a6b1297210c5e24c76b9a936250a1ce2721576c26ea797c7ec35f9e46a9"), 128UL));
        }

        {
            auto snapshot = state_ref.at(MerkleTreeId::L1_TO_L2_MESSAGE_TREE);
            EXPECT_EQ(
                snapshot,
                std::make_pair(bb::fr("0x14f44d672eb357739e42463497f9fdac46623af863eea4d947ca00a497dcdeb3"), 0UL));
        }
    }
}

TEST_F(WorldStateTest, GetInitialStateReference)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);

    auto before_commit = ws.get_initial_state_reference();
    ws.append_leaves<bb::fr>(MerkleTreeId::NOTE_HASH_TREE, { 1 });
    ws.commit();

    auto after_commit = ws.get_initial_state_reference();

    EXPECT_EQ(before_commit, after_commit);
}

TEST_F(WorldStateTest, AppendOnlyTrees)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);

    // the trees that start out empty
    std::vector tree_ids{ MerkleTreeId::NOTE_HASH_TREE, MerkleTreeId::L1_TO_L2_MESSAGE_TREE };

    for (auto tree_id : tree_ids) {
        auto initial = ws.get_tree_info(WorldStateRevision::committed(), tree_id);
        assert_leaf_status<fr>(ws, WorldStateRevision::committed(), tree_id, 0, false);

        ws.append_leaves<fr>(tree_id, { fr(42) });
        assert_leaf_value(ws, WorldStateRevision::uncommitted(), tree_id, 0, fr(42));
        assert_leaf_status<fr>(ws, WorldStateRevision::committed(), tree_id, 0, false);
        assert_leaf_index(ws, WorldStateRevision::uncommitted(), tree_id, fr(42), 0);

        auto uncommitted = ws.get_tree_info(WorldStateRevision::uncommitted(), tree_id);
        // uncommitted state diverges from committed state
        EXPECT_EQ(uncommitted.meta.size, initial.meta.size + 1);
        EXPECT_NE(uncommitted.meta.root, initial.meta.root);

        assert_sibling_path(ws, WorldStateRevision::uncommitted(), tree_id, uncommitted.meta.root, fr(42), 0);

        auto committed = ws.get_tree_info(WorldStateRevision::committed(), tree_id);
        EXPECT_EQ(committed.meta.size, initial.meta.size);
        EXPECT_EQ(committed.meta.root, initial.meta.root);

        ws.commit();
        assert_leaf_value(ws, WorldStateRevision::committed(), tree_id, 0, fr(42));
        assert_leaf_index(ws, WorldStateRevision::committed(), tree_id, fr(42), 0);

        auto after_commit = ws.get_tree_info(WorldStateRevision::committed(), tree_id);
        // commiting updates the committed state
        EXPECT_EQ(after_commit.meta.size, uncommitted.meta.size);
        EXPECT_EQ(after_commit.meta.root, uncommitted.meta.root);

        assert_sibling_path(ws, WorldStateRevision::committed(), tree_id, after_commit.meta.root, fr(42), 0);

        ws.append_leaves<fr>(tree_id, { fr(43) });
        assert_leaf_value(ws, WorldStateRevision::uncommitted(), tree_id, 1, fr(43));
        assert_leaf_status<fr>(ws, WorldStateRevision::committed(), tree_id, 1, false);
        assert_leaf_index(ws, WorldStateRevision::uncommitted(), tree_id, fr(43), 1);

        auto before_rollback = ws.get_tree_info(WorldStateRevision::uncommitted(), tree_id);
        EXPECT_EQ(before_rollback.meta.size, after_commit.meta.size + 1);
        EXPECT_NE(before_rollback.meta.root, after_commit.meta.root);

        ws.rollback();
        assert_leaf_status<fr>(ws, WorldStateRevision::uncommitted(), tree_id, 1, false);
        assert_leaf_status<fr>(ws, WorldStateRevision::committed(), tree_id, 1, false);

        auto after_rollback = ws.get_tree_info(WorldStateRevision::committed(), tree_id);
        // rollback restores the committed state
        EXPECT_EQ(after_rollback.meta.size, after_commit.meta.size);
        EXPECT_EQ(after_rollback.meta.root, after_commit.meta.root);
    }
}

TEST_F(WorldStateTest, AppendOnlyAllowDuplicates)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);

    // the trees that start out empty
    std::vector tree_ids{
        MerkleTreeId::NOTE_HASH_TREE,
        MerkleTreeId::L1_TO_L2_MESSAGE_TREE,
    };

    for (auto tree_id : tree_ids) {
        ws.append_leaves<fr>(tree_id, { fr(42), fr(42) });
        ws.append_leaves<fr>(tree_id, { fr(42) });

        assert_leaf_value(ws, WorldStateRevision::uncommitted(), tree_id, 0, fr(42));
        assert_leaf_value(ws, WorldStateRevision::uncommitted(), tree_id, 1, fr(42));
        assert_leaf_value(ws, WorldStateRevision::uncommitted(), tree_id, 2, fr(42));

        ws.commit();

        assert_leaf_value(ws, WorldStateRevision::committed(), tree_id, 0, fr(42));
        assert_leaf_value(ws, WorldStateRevision::committed(), tree_id, 1, fr(42));
        assert_leaf_value(ws, WorldStateRevision::committed(), tree_id, 2, fr(42));
    }
}

TEST_F(WorldStateTest, NullifierTree)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);
    auto tree_id = MerkleTreeId::NULLIFIER_TREE;
    NullifierLeafValue test_nullifier(142);

    auto predecessor_of_142 =
        ws.find_low_leaf_index(WorldStateRevision::committed(), tree_id, test_nullifier.get_key());
    EXPECT_EQ(predecessor_of_142, GetLowIndexedLeafResponse(false, 127UL));

    ws.append_leaves<NullifierLeafValue>(tree_id, { test_nullifier });
    assert_leaf_value(ws, WorldStateRevision::uncommitted(), tree_id, 128, test_nullifier);

    ws.commit();

    auto test_leaf = ws.get_indexed_leaf<NullifierLeafValue>(WorldStateRevision::committed(), tree_id, 128);
    // at this point 142 should be the biggest leaf so it wraps back to 0
    EXPECT_EQ(test_leaf.value(), IndexedLeaf(test_nullifier, 0, 0));

    auto predecessor_of_142_again =
        ws.find_low_leaf_index(WorldStateRevision::committed(), tree_id, test_nullifier.get_key());
    EXPECT_EQ(predecessor_of_142_again, GetLowIndexedLeafResponse(true, 128UL));

    auto predecessor_of_143 = ws.find_low_leaf_index(WorldStateRevision::committed(), tree_id, 143);
    EXPECT_EQ(predecessor_of_143,
              GetLowIndexedLeafResponse(false, 128UL)); // predecessor is going to be nullifier 142 on slot 127

    auto info = ws.get_tree_info(WorldStateRevision::committed(), tree_id);
    assert_sibling_path(ws,
                        WorldStateRevision::committed(),
                        tree_id,
                        info.meta.root,
                        HashPolicy::hash(test_leaf.value().get_hash_inputs()),
                        128);
}

TEST_F(WorldStateTest, NullifierTreeDuplicates)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);
    auto tree_id = MerkleTreeId::NULLIFIER_TREE;
    NullifierLeafValue test_nullifier(142);

    ws.append_leaves<NullifierLeafValue>(tree_id, { test_nullifier });
    ws.commit();

    assert_tree_size(ws, WorldStateRevision::committed(), tree_id, 129);
    EXPECT_THROW(ws.append_leaves<NullifierLeafValue>(tree_id, { test_nullifier }), std::runtime_error);
    assert_tree_size(ws, WorldStateRevision::committed(), tree_id, 129);
}

TEST_F(WorldStateTest, NullifierBatchInsert)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);
    auto response = ws.batch_insert_indexed_leaves<NullifierLeafValue>(
        MerkleTreeId::NULLIFIER_TREE, { NullifierLeafValue(150), NullifierLeafValue(142), NullifierLeafValue(180) }, 2);

    std::vector<std::pair<NullifierLeafValue, size_t>> expected_sorted_leaves = { { NullifierLeafValue(180), 2 },
                                                                                  { NullifierLeafValue(150), 0 },
                                                                                  { NullifierLeafValue(142), 1 } };
    EXPECT_EQ(response.sorted_leaves, expected_sorted_leaves);

    {
        // insertion happens in descending order, but keeping original indices
        // first insert leaf 180, at index 130 (tree had size 127, 180 is the third item => 127 + 3)
        // predecessor will be 127, currently linked to head of the list (0)
        auto low_leaf = response.low_leaf_witness_data[0];
        auto expected_low_leaf = IndexedLeaf(NullifierLeafValue(127), 0, fr(0));
        EXPECT_EQ(low_leaf.index, 127);
        EXPECT_EQ(low_leaf.leaf, expected_low_leaf);
    }

    {
        // insert 150 on position 128 (127 + 1)
        // predecessor will be 127 linked to 180
        auto low_leaf = response.low_leaf_witness_data[1];
        auto expected_low_leaf = IndexedLeaf(NullifierLeafValue(127), 130, fr(180));
        EXPECT_EQ(low_leaf.index, 127);
        EXPECT_EQ(low_leaf.leaf, expected_low_leaf);
    }

    {
        // finally, insert 142 on position 129(127 + 2)
        // prededecessor will be 127 linked to 150
        auto low_leaf = response.low_leaf_witness_data[2];
        auto expected_low_leaf = IndexedLeaf(NullifierLeafValue(127), 128, fr(150));
        EXPECT_EQ(low_leaf.index, 127);
        EXPECT_EQ(low_leaf.leaf, expected_low_leaf);
    }
}

TEST_F(WorldStateTest, PublicDataTree)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);

    ws.append_leaves(MerkleTreeId::PUBLIC_DATA_TREE, std::vector{ PublicDataLeafValue(142, 0) });
    assert_tree_size(ws, WorldStateRevision::uncommitted(), MerkleTreeId::PUBLIC_DATA_TREE, 129);

    auto leaf = ws.get_indexed_leaf<PublicDataLeafValue>(
        WorldStateRevision::uncommitted(), MerkleTreeId::PUBLIC_DATA_TREE, 128);
    EXPECT_EQ(leaf.value().value, PublicDataLeafValue(142, 0));

    ws.update_public_data(PublicDataLeafValue(142, 1));
    // updating insert a dummy leaf
    assert_tree_size(ws, WorldStateRevision::uncommitted(), MerkleTreeId::PUBLIC_DATA_TREE, 130);

    leaf = ws.get_indexed_leaf<PublicDataLeafValue>(
        WorldStateRevision::uncommitted(), MerkleTreeId::PUBLIC_DATA_TREE, 128);
    EXPECT_EQ(leaf.value().value, PublicDataLeafValue(142, 1));
}

TEST_F(WorldStateTest, CommitsAndRollsBackAllTrees)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);

    ws.append_leaves<fr>(MerkleTreeId::NOTE_HASH_TREE, { fr(42) });
    ws.append_leaves<fr>(MerkleTreeId::L1_TO_L2_MESSAGE_TREE, { fr(42) });
    ws.append_leaves<fr>(MerkleTreeId::ARCHIVE, { fr(42) });
    ws.append_leaves<NullifierLeafValue>(MerkleTreeId::NULLIFIER_TREE, { NullifierLeafValue(142) });
    ws.append_leaves<PublicDataLeafValue>(MerkleTreeId::PUBLIC_DATA_TREE, { PublicDataLeafValue(142, 1) });

    ws.commit();

    assert_leaf_value(ws, WorldStateRevision::committed(), MerkleTreeId::NOTE_HASH_TREE, 0, fr(42));
    assert_leaf_value(ws, WorldStateRevision::committed(), MerkleTreeId::L1_TO_L2_MESSAGE_TREE, 0, fr(42));
    assert_leaf_value(ws, WorldStateRevision::committed(), MerkleTreeId::ARCHIVE, 1, fr(42));
    assert_leaf_value(ws, WorldStateRevision::committed(), MerkleTreeId::NULLIFIER_TREE, 128, NullifierLeafValue(142));
    assert_leaf_value(
        ws, WorldStateRevision::committed(), MerkleTreeId::PUBLIC_DATA_TREE, 128, PublicDataLeafValue(142, 1));

    ws.append_leaves<fr>(MerkleTreeId::NOTE_HASH_TREE, { fr(43) });
    ws.append_leaves<fr>(MerkleTreeId::L1_TO_L2_MESSAGE_TREE, { fr(43) });
    ws.append_leaves<fr>(MerkleTreeId::ARCHIVE, { fr(43) });
    ws.append_leaves<NullifierLeafValue>(MerkleTreeId::NULLIFIER_TREE, { NullifierLeafValue(143) });
    ws.append_leaves<PublicDataLeafValue>(MerkleTreeId::PUBLIC_DATA_TREE, { PublicDataLeafValue(143, 1) });

    ws.rollback();

    assert_leaf_exists(ws, WorldStateRevision::committed(), MerkleTreeId::NOTE_HASH_TREE, fr(43), false);
    assert_leaf_exists(ws, WorldStateRevision::committed(), MerkleTreeId::L1_TO_L2_MESSAGE_TREE, fr(43), false);
    assert_leaf_exists(ws, WorldStateRevision::committed(), MerkleTreeId::ARCHIVE, fr(43), false);
    assert_leaf_exists(
        ws, WorldStateRevision::committed(), MerkleTreeId::NULLIFIER_TREE, NullifierLeafValue(143), false);
    assert_leaf_exists(
        ws, WorldStateRevision::committed(), MerkleTreeId::PUBLIC_DATA_TREE, PublicDataLeafValue(143, 1), false);
}

TEST_F(WorldStateTest, SyncExternalBlockFromEmpty)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);
    StateReference block_state_ref = {
        { MerkleTreeId::NULLIFIER_TREE,
          { fr("0x0342578609a7358092788d0eed7d1ee0ec8e0c596c0b1e85ba980ddd5cc79d04"), 129 } },
        { MerkleTreeId::NOTE_HASH_TREE,
          { fr("0x15dad063953d8d216c1db77739d6fb27e1b73a5beef748a1208898b3428781eb"), 1 } },
        { MerkleTreeId::PUBLIC_DATA_TREE,
          { fr("0x0278dcf9ff541da255ee722aecfad849b66af0d42c2924d949b5a509f2e1aec9"), 129 } },
        { MerkleTreeId::L1_TO_L2_MESSAGE_TREE,
          { fr("0x20ea8ca97f96508aaed2d6cdc4198a41c77c640bfa8785a51bb905b9a672ba0b"), 1 } },
    };

    bool sync_res = ws.sync_block(
        block_state_ref, fr(1), { 42 }, { 43 }, { NullifierLeafValue(144) }, { { PublicDataLeafValue(145, 1) } });
    EXPECT_EQ(sync_res, false);

    assert_leaf_value(ws, WorldStateRevision::committed(), MerkleTreeId::NOTE_HASH_TREE, 0, fr(42));
    assert_leaf_value(ws, WorldStateRevision::committed(), MerkleTreeId::L1_TO_L2_MESSAGE_TREE, 0, fr(43));
    assert_leaf_value(ws, WorldStateRevision::committed(), MerkleTreeId::NULLIFIER_TREE, 128, NullifierLeafValue(144));
    assert_leaf_value(
        ws, WorldStateRevision::committed(), MerkleTreeId::PUBLIC_DATA_TREE, 128, PublicDataLeafValue(145, 1));
    assert_leaf_value(ws, WorldStateRevision::committed(), MerkleTreeId::ARCHIVE, 1, fr(1));

    auto state_ref = ws.get_state_reference(WorldStateRevision::committed());
    for (const auto& [tree_id, snapshot] : block_state_ref) {
        EXPECT_EQ(state_ref.at(tree_id), snapshot);
    }
}

TEST_F(WorldStateTest, SyncBlockFromDirtyState)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);
    StateReference block_state_ref = {
        { MerkleTreeId::NULLIFIER_TREE,
          { fr("0x0342578609a7358092788d0eed7d1ee0ec8e0c596c0b1e85ba980ddd5cc79d04"), 129 } },
        { MerkleTreeId::NOTE_HASH_TREE,
          { fr("0x15dad063953d8d216c1db77739d6fb27e1b73a5beef748a1208898b3428781eb"), 1 } },
        { MerkleTreeId::PUBLIC_DATA_TREE,
          { fr("0x0278dcf9ff541da255ee722aecfad849b66af0d42c2924d949b5a509f2e1aec9"), 129 } },
        { MerkleTreeId::L1_TO_L2_MESSAGE_TREE,
          { fr("0x20ea8ca97f96508aaed2d6cdc4198a41c77c640bfa8785a51bb905b9a672ba0b"), 1 } },
    };

    ws.append_leaves<fr>(MerkleTreeId::NOTE_HASH_TREE, { fr(142) });
    ws.append_leaves<fr>(MerkleTreeId::L1_TO_L2_MESSAGE_TREE, { fr(143) });
    ws.append_leaves<NullifierLeafValue>(MerkleTreeId::NULLIFIER_TREE, { NullifierLeafValue(142) });
    ws.append_leaves<PublicDataLeafValue>(MerkleTreeId::PUBLIC_DATA_TREE, { PublicDataLeafValue(142, 1) });

    auto uncommitted_state_ref = ws.get_state_reference(WorldStateRevision::uncommitted());
    for (const auto& [tree_id, snapshot] : block_state_ref) {
        EXPECT_NE(uncommitted_state_ref.at(tree_id), snapshot);
    }

    bool sync_res = ws.sync_block(
        block_state_ref, fr(1), { 42 }, { 43 }, { NullifierLeafValue(144) }, { { PublicDataLeafValue(145, 1) } });
    EXPECT_EQ(sync_res, false);

    assert_leaf_value(ws, WorldStateRevision::committed(), MerkleTreeId::NOTE_HASH_TREE, 0, fr(42));
    assert_leaf_value(ws, WorldStateRevision::committed(), MerkleTreeId::L1_TO_L2_MESSAGE_TREE, 0, fr(43));
    assert_leaf_value(ws, WorldStateRevision::committed(), MerkleTreeId::NULLIFIER_TREE, 128, NullifierLeafValue(144));
    assert_leaf_value(
        ws, WorldStateRevision::committed(), MerkleTreeId::PUBLIC_DATA_TREE, 128, PublicDataLeafValue(145, 1));
    assert_leaf_value(ws, WorldStateRevision::committed(), MerkleTreeId::ARCHIVE, 1, fr(1));

    auto state_ref = ws.get_state_reference(WorldStateRevision::committed());
    for (const auto& [tree_id, snapshot] : block_state_ref) {
        EXPECT_EQ(state_ref.at(tree_id), snapshot);
    }
}

TEST_F(WorldStateTest, SyncCurrentBlock)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);
    bb::fr block_hash(1);
    StateReference block_state_ref = {
        { MerkleTreeId::NULLIFIER_TREE,
          { fr("0x0342578609a7358092788d0eed7d1ee0ec8e0c596c0b1e85ba980ddd5cc79d04"), 129 } },
        { MerkleTreeId::NOTE_HASH_TREE,
          { fr("0x15dad063953d8d216c1db77739d6fb27e1b73a5beef748a1208898b3428781eb"), 1 } },
        { MerkleTreeId::PUBLIC_DATA_TREE,
          { fr("0x0278dcf9ff541da255ee722aecfad849b66af0d42c2924d949b5a509f2e1aec9"), 129 } },
        { MerkleTreeId::L1_TO_L2_MESSAGE_TREE,
          { fr("0x20ea8ca97f96508aaed2d6cdc4198a41c77c640bfa8785a51bb905b9a672ba0b"), 1 } },
    };

    ws.append_leaves<fr>(MerkleTreeId::NOTE_HASH_TREE, { 42 });
    ws.append_leaves<fr>(MerkleTreeId::L1_TO_L2_MESSAGE_TREE, { 43 });
    ws.append_leaves<NullifierLeafValue>(MerkleTreeId::NULLIFIER_TREE, { NullifierLeafValue(144) });
    ws.append_leaves<PublicDataLeafValue>(MerkleTreeId::PUBLIC_DATA_TREE, { PublicDataLeafValue(145, 1) });
    ws.append_leaves<fr>(MerkleTreeId::ARCHIVE, { block_hash });

    auto uncommitted_state_ref = ws.get_state_reference(WorldStateRevision::uncommitted());
    for (const auto& [tree_id, snapshot] : block_state_ref) {
        EXPECT_EQ(uncommitted_state_ref.at(tree_id), snapshot);
    }

    bool sync_res = ws.sync_block(
        block_state_ref, fr(1), { 42 }, { 43 }, { NullifierLeafValue(144) }, { { PublicDataLeafValue(145, 1) } });
    EXPECT_EQ(sync_res, true);

    assert_leaf_value(ws, WorldStateRevision::uncommitted(), MerkleTreeId::ARCHIVE, 1, fr(1));

    auto state_ref = ws.get_state_reference(WorldStateRevision::committed());
    for (const auto& [tree_id, snapshot] : block_state_ref) {
        EXPECT_EQ(state_ref.at(tree_id), snapshot);
    }
}

TEST_F(WorldStateTest, RejectSyncBlockWithBadPublicWriteBatches)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);
    StateReference block_state_ref = {
        { MerkleTreeId::NULLIFIER_TREE,
          { fr("0x0342578609a7358092788d0eed7d1ee0ec8e0c596c0b1e85ba980ddd5cc79d04"), 129 } },
        { MerkleTreeId::NOTE_HASH_TREE,
          { fr("0x15dad063953d8d216c1db77739d6fb27e1b73a5beef748a1208898b3428781eb"), 1 } },
        { MerkleTreeId::PUBLIC_DATA_TREE,
          { fr("0x0278dcf9ff541da255ee722aecfad849b66af0d42c2924d949b5a509f2e1aec9"), 129 } },
        { MerkleTreeId::L1_TO_L2_MESSAGE_TREE,
          { fr("0x20ea8ca97f96508aaed2d6cdc4198a41c77c640bfa8785a51bb905b9a672ba0b"), 1 } },
    };

    auto sync = [&]() {
        return ws.sync_block(block_state_ref,
                             fr(1),
                             { 42 },
                             { 43 },
                             { NullifierLeafValue(144) },
                             // this should be rejected because we can't have duplicate slots in the same batch
                             { { PublicDataLeafValue(145, 1), PublicDataLeafValue(145, 2) } });
    };

    EXPECT_THROW(sync(), std::runtime_error);
}

TEST_F(WorldStateTest, RejectSyncBlockWithInvalidStateRef)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);
    StateReference block_state_ref = {
        { MerkleTreeId::NULLIFIER_TREE,
          { fr("0x0342578609a7358092788d0eed7d1ee0ec8e0c596c0b1e85ba980ddd5cc79d04"), 129 } },
        { MerkleTreeId::NOTE_HASH_TREE,
          { fr("0x15dad063953d8d216c1db77739d6fb27e1b73a5beef748a1208898b3428781eb"), 1 } },
        { MerkleTreeId::PUBLIC_DATA_TREE,
          { fr("0x0278dcf9ff541da255ee722aecfad849b66af0d42c2924d949b5a509f2e1aec9"), 129 } },
        { MerkleTreeId::L1_TO_L2_MESSAGE_TREE,
          { fr("0x20ea8ca97f96508aaed2d6cdc4198a41c77c640bfa8785a51bb905b9a672ba0b"), 1 } },
    };

    auto sync = [&]() {
        return ws.sync_block(block_state_ref,
                             fr(1),
                             { 42 },
                             { 43 },
                             { NullifierLeafValue(144) },
                             // this should be rejected because public data tree root will not match the state ref above
                             // (state ref above is for slot[145]=1, not slot[145]=2)
                             { { PublicDataLeafValue(145, 2) } });
    };

    EXPECT_THROW(sync(), std::runtime_error);
}

TEST_F(WorldStateTest, SyncEmptyBlock)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);
    StateReference block_state_ref = ws.get_state_reference(WorldStateRevision::committed());
    ws.sync_block(block_state_ref, fr(1), {}, {}, {}, {});
    StateReference after_sync = ws.get_state_reference(WorldStateRevision::committed());
    EXPECT_EQ(block_state_ref, after_sync);
    EXPECT_EQ(ws.find_leaf_index(WorldStateRevision::committed(), MerkleTreeId::ARCHIVE, fr(1)), 1);
}

TEST_F(WorldStateTest, ForkingAtBlock0SameState)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);
    auto fork_id = ws.create_fork(0);

    assert_fork_state_unchanged(ws, fork_id, false);
    assert_fork_state_unchanged(ws, fork_id, true);
}

TEST_F(WorldStateTest, ForkingAtBlock0AndAdvancingFork)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);
    auto fork_id = ws.create_fork(0);

    auto canonical_archive_state_before = ws.get_tree_info(WorldStateRevision::uncommitted(), MerkleTreeId::ARCHIVE);
    auto fork_archive_state_before = ws.get_tree_info(
        WorldStateRevision{
            .forkId = fork_id,
            .includeUncommitted = true,
        },
        MerkleTreeId::ARCHIVE);

    ws.append_leaves<bb::fr>(MerkleTreeId::ARCHIVE, { fr(1) }, fork_id);

    auto canonical_archive_state_after = ws.get_tree_info(WorldStateRevision::uncommitted(), MerkleTreeId::ARCHIVE);
    auto fork_archive_state_after = ws.get_tree_info(
        WorldStateRevision{
            .forkId = fork_id,
            .includeUncommitted = true,
        },
        MerkleTreeId::ARCHIVE);

    EXPECT_EQ(canonical_archive_state_after.meta, canonical_archive_state_before.meta);
    EXPECT_EQ(fork_archive_state_before.meta, canonical_archive_state_before.meta);
    EXPECT_NE(fork_archive_state_after.meta, fork_archive_state_before.meta);
}

TEST_F(WorldStateTest, ForkingAtBlock0AndAdvancingCanonicalState)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);
    auto fork_id = ws.create_fork(0);

    auto canonical_archive_state_before = ws.get_tree_info(WorldStateRevision::uncommitted(), MerkleTreeId::ARCHIVE);
    auto fork_archive_state_before_insert = ws.get_tree_info(
        WorldStateRevision{
            .forkId = fork_id,
            .includeUncommitted = true,
        },
        MerkleTreeId::ARCHIVE);

    // fork the state
    ws.append_leaves<bb::fr>(MerkleTreeId::ARCHIVE, { fr(1) });
    ws.append_leaves<bb::fr>(MerkleTreeId::ARCHIVE, { fr(2) }, fork_id);

    auto canonical_archive_state_after_insert =
        ws.get_tree_info(WorldStateRevision::uncommitted(), MerkleTreeId::ARCHIVE);
    auto fork_archive_state_after_insert = ws.get_tree_info(
        WorldStateRevision{
            .forkId = fork_id,
            .includeUncommitted = true,
        },
        MerkleTreeId::ARCHIVE);

    EXPECT_EQ(fork_archive_state_before_insert.meta, canonical_archive_state_before.meta);

    EXPECT_NE(canonical_archive_state_after_insert.meta, canonical_archive_state_before.meta);
    EXPECT_NE(fork_archive_state_after_insert.meta, fork_archive_state_before_insert.meta);
    EXPECT_NE(fork_archive_state_after_insert.meta, canonical_archive_state_after_insert.meta);

    ws.commit();
    auto canonical_archive_state_after_commit =
        ws.get_tree_info(WorldStateRevision::committed(), MerkleTreeId::ARCHIVE);
    auto fork_archive_state_after_commit = ws.get_tree_info(
        WorldStateRevision{
            .forkId = fork_id,
            .includeUncommitted = false,
        },
        MerkleTreeId::ARCHIVE);

    // committed fork state should match the state before fork had been modified
    EXPECT_EQ(fork_archive_state_after_commit.meta, fork_archive_state_before_insert.meta);
    // canonical state before commit should match state after commit
    // EXPECT_EQ(canonical_archive_state_after_commit.meta, canonical_archive_state_after_insert.meta);
    EXPECT_EQ(canonical_archive_state_after_commit.meta.root, canonical_archive_state_after_insert.meta.root);
    EXPECT_EQ(canonical_archive_state_after_commit.meta.size, canonical_archive_state_after_insert.meta.size);

    // canonical should have value 1 as the first leaf (committed state)
    assert_leaf_value<bb::fr>(ws, WorldStateRevision{ .includeUncommitted = false }, MerkleTreeId::ARCHIVE, 1, 1);
    // fork should still have value 2 as the first leaf (uncommitted)
    assert_leaf_value<bb::fr>(
        ws, WorldStateRevision{ .forkId = fork_id, .includeUncommitted = true }, MerkleTreeId::ARCHIVE, 1, 2);
}

TEST_F(WorldStateTest, BuildsABlockInAFork)
{
    WorldState ws(thread_pool_size, data_dir, map_size, tree_heights, tree_prefill, initial_header_generator_point);
    auto fork_id = ws.create_fork(0);

    ws.append_leaves<bb::fr>(MerkleTreeId::NOTE_HASH_TREE, { 42 }, fork_id);
    ws.append_leaves<bb::fr>(MerkleTreeId::L1_TO_L2_MESSAGE_TREE, { 43 }, fork_id);
    ws.batch_insert_indexed_leaves<NullifierLeafValue>(MerkleTreeId::NULLIFIER_TREE, { { 129 } }, 0, fork_id);
    ws.batch_insert_indexed_leaves<PublicDataLeafValue>(MerkleTreeId::PUBLIC_DATA_TREE, { { 129, 1 } }, 0, fork_id);

    auto fork_state_ref = ws.get_state_reference(WorldStateRevision{ .forkId = fork_id, .includeUncommitted = true });

    ws.update_archive(fork_state_ref, { 1 }, fork_id);
    auto fork_archive =
        ws.get_tree_info(WorldStateRevision{ .forkId = fork_id, .includeUncommitted = true }, MerkleTreeId::ARCHIVE);

    ws.delete_fork(fork_id);

    ws.sync_block(fork_state_ref, { 1 }, { 42 }, { 43 }, { { 129 } }, { { { 129, 1 } } });

    EXPECT_EQ(fork_state_ref, ws.get_state_reference(WorldStateRevision::committed()));
}