// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The LIVEsCOIN team
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include "net.h"
#include "base58.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x00000875ad328632b5ccaf4e1dc1d30c886a166b72cc7442c1352c447d661e4d"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1541248668, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x000006a349bf407274e599b83c193f5f4eecc433cd0470d49c838b1039757d4d"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1541248669,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1541248670,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        vTreasuryRewardAddress_old = "LbTk7HV6ro6ro8N4BmPVq5sreErhweBMWV";
        vTreasuryRewardAddress = "LQoqgdSJQ19BasHBxoFLWms9hVbHjmtw5H";
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x7c;
        pchMessageStart[1] = 0xd3;
        pchMessageStart[2] = 0x6d;
        pchMessageStart[3] = 0x52;
        vAlertPubKey = ParseHex("0403ae9074d5eb74f3e1d73cb831205cddd521957512620bcd3674f8cf9a4f3e5dde95db52f7ae2726362a607b9cd2baadcdc1fc840a067a95a327a1dccde6d617");
        nDefaultPort = 17310;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // LIVEsCOIN starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 1000000; // Halving rewards every 1 mil blocks
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // LIVEsCOIN: 1 minute
        nTargetSpacing = 1 * 60; //LIVEsCOIN: 1 minute
        nMaturity = 40;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 14000000000 * COIN; //14,000,000,000

        /** Height or Time Based Activations **/
        nLastPOWBlock = 86399;
        nModifierUpdateBlock = 999999999;
        nZerocoinStartHeight = 86400;
        nAccumulatorStartHeight = 1;
        nZerocoinStartTime = 1531216800; // Mon, 09 Jul 2018 20:00 - UTC
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = ~1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = ~1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = ~1; //Last valid accumulator checkpoint


        const char* pszTimestamp = "Create LIVEsCOIN 03/11/2018";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0493ed23f5552bee413e5355de6ca7a088f69a0b66244aef572cc2bad38e1930b93513ec48b518ea9b37ec9d9d69756aa0549ecd256befc242f099aa91d63d1246") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1541248668;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 3630114;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000875ad328632b5ccaf4e1dc1d30c886a166b72cc7442c1352c447d661e4d"));
        assert(genesis.hashMerkleRoot == uint256("0xb73c9180a9f20b594d0bffddd3c8c003ed0964d5d3679371eee156477c7714f7"));

        vSeeds.push_back(CDNSSeedData("108.61.161.237", "108.61.161.237"));
        vSeeds.push_back(CDNSSeedData("202.182.126.191", "202.182.126.191"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 48);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 43);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x02)(0x2D)(0x25)(0x14).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x02)(0x21)(0x31)(0x1B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x5b).convert_to_container<std::vector<unsigned char> >();


        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04f3470a2b93fc9dc98fedb0b55d4de56e766a3b8d0f71781f94009e0cdb12368fd863d1dac6ad654d5d6e3aef08c5788529599dadb4ebc535dfa08ba8f1ad5136";
        strObfuscationPoolDummyAddress = "LiHbaZJKGaqWQyXH75GvziLCqSRsvumzi1";
        nStartMasternodePayments = 1531224000; // Tue, 10 Jul 2018 12:00 UTC

        /** Zerocoin */
        zerocoinModulus = "8088860057868861737579906159271427005891321755007079630831849683771300410123758233394747140020264352026082915534"
            "1353487781732964594494627908018297937846777788008247147155101224868589394266794718810240014829739291226941282235"
            "0560668723583271706172809251221409558942062655165272775918262756354801182402411263859445737545487801319121924032"
            "1192836922276789791132865101810862181027881795838163627905473547640390439094528337127298742284922817821910494377"
            "1708210679220077175523213028147100998461362945100290849499912776380217996745211296052879222831799629200187098027"
            "1414290277902511499837025670466025140661314335560617109504424122225015827298001318290284987086940604918768910788";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * ZCENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};

std::string CChainParams::GetTreasuryRewardAddress(bool fNewAddress) const {
    if (fNewAddress) {
        return vTreasuryRewardAddress;
    } else {
        return vTreasuryRewardAddress_old;
    }
}

CScript CChainParams::GetTreasuryRewardScript(bool fNewAddress) const {
    CBitcoinAddress address(GetTreasuryRewardAddress(fNewAddress).c_str());
    assert(address.IsValid());

    CScript script = GetScriptForDestination(address.Get());
    return script;
}

std::string CChainParams::GetTreasuryRewardAddressAtHeight(int nHeight) const {
    return vTreasuryRewardAddress;
}

CScript CChainParams::GetTreasuryRewardScriptAtHeight(int nHeight) const {
    CBitcoinAddress address(GetTreasuryRewardAddressAtHeight(nHeight).c_str());
    assert(address.IsValid());

    CScript script = GetScriptForDestination(address.Get());
    return script;
}

static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x13;
        pchMessageStart[1] = 0x63;
        pchMessageStart[2] = 0x69;
        pchMessageStart[3] = 0x78;
        vAlertPubKey = ParseHex("043dfe7ce3028e574a116510fe6810c01e211d9ae68f20f4b180d3e7183328d3e79196b8a47b13bd4142d4f9e314eb5a0f7bf56590c4ceb398df9b0e956eaa91eb");
        nDefaultPort = 17312;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // LIVEsCOIN: 1 minute
        nTargetSpacing = 1 * 60;  // LIVEsCOIN: 1 minute
        nLastPOWBlock = 10079;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197;
        nMaxMoneyOut = 14000000000 * COIN;
        nZerocoinStartHeight = 10080;
        nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1541248669;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 369811;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x000006a349bf407274e599b83c193f5f4eecc433cd0470d49c838b1039757d4d"));
        assert(genesis.hashMerkleRoot == uint256("0xb73c9180a9f20b594d0bffddd3c8c003ed0964d5d3679371eee156477c7714f7"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet livescoin addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19); // Testnet livescoin script addresses start with '8' or '9'
	base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
	base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x02)(0x3D)(0x6c)(0x11).convert_to_container<std::vector<unsigned char> >();
	base58Prefixes[EXT_SECRET_KEY] = list_of(0x02)(0x31)(0x2b)(0x2F).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xbc).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "0493ed23f5552bee413e5355de6ca7a088f69a0b66244aef572cc2bad38e1930b93513ec48b518ea9b37ec9d9d69756aa0549ecd256befc242f099aa91d63d1246";
        strObfuscationPoolDummyAddress = "BPh3acK5Nb7QSnKYCSTwxV5vAm3U3CU3tR";
        nStartMasternodePayments = 1531217400;
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x69;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x75;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // LIVEsCOIN: 1 day
        nTargetSpacing = 1 * 60;        // LIVEsCOIN: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1541248670;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 0;

        hashGenesisBlock = genesis.GetHash();

/*
            printf("calc new genesis block\n");
            printf("hashMerkleRoot %s\n", genesis.hashMerkleRoot.ToString().c_str());
            printf("bnProofOfWorkLimit 0x%x\n", bnProofOfWorkLimit.GetCompact());
            printf("genesis.nBits 0x%x\n", genesis.nBits);

            for (genesis.nNonce = 0; ; genesis.nNonce++) {
                hashGenesisBlock = genesis.GetHash();
                if (hashGenesisBlock <= bnProofOfWorkLimit) break;
            }

            printf("hashGenesisBlock %s\n", hashGenesisBlock.ToString().c_str());
            printf("genesis.nNonce %d\n", genesis.nNonce);

*/

        assert(hashGenesisBlock == uint256("0x75e93300e67c2798dd3c86598555833f0325c6ab41c978e38875d9843baa930c"));
        nDefaultPort = 17314;

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 31476;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
