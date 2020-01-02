// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "../Data.h"
#include "../PublicKey.h"

#include <string>
#include <optional>

namespace TW::FIO {

class Address {
public:
    /// Number of bytes in an address, public key size + checksum
    static const size_t size = PublicKey::secp256k1Size + 4;

    /// Address data consisting of a prefix byte followed by the public key
    /// hash.
    std::array<byte, size> bytes;

    /// Determines whether a string makes a valid FIO address.
    static bool isValid(const std::string& string);

    /// Determines whether a string makes a valid FIO address.
    static bool isValid(const Data& bytes);

    /// Initializes a FIO address from a string representation.
    Address(const std::string& string);

    /// Initializes a FIO address from a public key.
    Address(const PublicKey& publicKey);

    /// Returns a string representation of the FIO address.
    std::string string() const;

    friend bool operator==(const Address& lhs, const Address& rhs);

    static std::string prefix() { return "FIO"; }

private:
    static uint32_t createChecksum(const Data& bytes);

    static std::optional<Data> decodeKeyData(const std::string& string);
};


inline bool operator==(const Address& lhs, const Address& rhs) {
    return lhs.bytes == rhs.bytes;
}

} // namespace TW::FIO

/// Wrapper for C interface.
struct TWFIOAddress {
    TW::FIO::Address impl;
};
