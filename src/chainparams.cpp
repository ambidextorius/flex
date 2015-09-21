// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x23;
        pchMessageStart[1] = 0x37;
        pchMessageStart[2] = 0x17;
        pchMessageStart[3] = 0x71;
        vAlertPubKey = ParseHex("048b0e7aadbf923f97425b880a4ab4149a728f9e3a0c4adfa3b7ff0a7760fec5bd80022fbcff91cb75d1853c7de15d1e7f94e9c1fce994063af86124925af22b1e");
        nDefaultPort = 30137;
        nRPCPort = 30138;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 21);

        const char* pszTimestamp = "Flux, nothing else";
        CTransaction txNew;
        txNew.nTime = 1442853000;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1442853000;
        genesis.nBits    = 0x1f00ffff; 
        genesis.nNonce   = 530454;

        hashGenesisBlock = genesis.GetHash();    

        assert(hashGenesisBlock == uint256("0x0000050fac6b705687a7f65826a382453173d059c23f8d6362f6936f0073aaea"));
        assert(genesis.hashMerkleRoot == uint256("0x44b99cceaf927e405b85c8c4972508d0f2d6ef98cd6441af48e5d3746fb933c0"));
        
        base58Prefixes[PUBKEY_ADDRESS] = list_of(35);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(85);
        base58Prefixes[SECRET_KEY] =     list_of(153);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0x22)(0x2C);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xC2)(0xC4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 10000;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//
/*
void MineGenesisForTestNet(CBlock genesis){
    // This will figure out a valid hash and Nonce if you're creating a different genesis block:
    uint256 hashTarget = CBigNum().SetCompact(Params().ProofOfWorkLimit().GetCompact()).getuint256();
    printf("Target: %s\n", hashTarget.GetHex().c_str());
    uint256 newhash = genesis.GetHash();
    uint256 besthash;
    memset(&besthash,0xFF,32);
    while (newhash > hashTarget) {
    	++genesis.nNonce;
        if (genesis.nNonce == 0){
            printf("NONCE WRAPPED, incrementing time");
            ++genesis.nTime;
        }
	newhash = genesis.GetHash();
	if(newhash < besthash){
	    besthash=newhash;
	    printf("New best: %s\n", newhash.GetHex().c_str());
	}
    }
    printf("Found Genesis, Nonce: %ld, Hash: %s\n", genesis.nNonce, genesis.GetHash().GetHex().c_str());
    exit(0);
}
*/
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x13;
        pchMessageStart[1] = 0x27;
        pchMessageStart[2] = 0x0f;
        pchMessageStart[3] = 0x31;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0435c38ffb14441df9894dca8741921d67a8130ff3c2fb81e2b0503b31722bae8f1a450865036c63044e0aa4708b205c575c7ddc18c73bd36641e20eceef8d095d");
        nDefaultPort = 31137;
        nRPCPort = 31138;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 0; 
        genesis.nNonce = 0;
        
        hashGenesisBlock = genesis.GetHash();  
        
        // assert(hashGenesisBlock == uint256("0x"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(125);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x77)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x38)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
