/*************************************************************************************************
Copyright (c) 2020 Cobo

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
in the file COPYING.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************************************/
/** Avoid duplicate definitions */
#ifndef MASON_WALLET_H
#define MASON_WALLET_H

/** Header file reference */
#include <stdint.h>
#include <stdbool.h>
#include <mason_key.h>
#include <crypto_api.h>

/** Variable declarations */
enum SupportEntropyBits
{
    Entropy128Bits = 128,
    Entropy192Bits = 192,
    Entropy224Bits = 224,
    Entropy256Bits = 256
};

#define MAX_MNEMONIC_SIZE 240
#define MAX_HDPATH_SIZE 61
#define MAX_PASSPHRASE_SIZE (128*4)

typedef struct mnemonic_s
{
    uint32_t size;
    uint8_t data[MAX_MNEMONIC_SIZE];
} mnemonic_t;

typedef struct wallet_seed_s
{
    uint32_t length;
    uint8_t data[SHA512_LEN];
} wallet_seed_t;

#define MAX_WALLET_SEGMENTS 10

typedef struct wallet_path_s
{
    uint32_t version;
    uint32_t segments[MAX_WALLET_SEGMENTS];
    uint8_t num_of_segments;
} wallet_path_t;

#define MAX_UPDATE_KEY_LEN 510

typedef struct update_key_s
{
    uint16_t len;
    uint8_t key[MAX_UPDATE_KEY_LEN];
} update_key_t;

#define UPDATE_KEY_LEN 422
extern uint8_t update_key_ex[UPDATE_KEY_LEN];

/** Function declarations */
bool mason_generate_entropy(uint8_t *output_entropy, uint16_t bits, bool need_checksum);
bool mason_wallet_setup(mnemonic_t *mnemonic, uint8_t *passphrase, uint16_t passphrase_len);
bool mason_create_wallet(uint8_t *mnemonic, uint16_t mnemonic_len);
bool mason_change_wallet_passphrase(uint8_t *passphrase, uint16_t passphrase_len);
bool mason_delete_wallet(void);

bool mason_update_key_load(update_key_t *update_key);
bool mason_update_key_save(const update_key_t *update_key);

bool mason_parse_wallet_path_from_string(char *string, uint16_t len, wallet_path_t *wallet_path);

bool mason_valid_wallet_path(wallet_path_t *wallet_path);

bool mason_verify_menonic(char *menonic, uint16_t len);
bool mason_mnemonic_read(mnemonic_t *mnemonic);
bool mason_mnemonic_write(mnemonic_t *mnemonic);
bool mason_seed_read(wallet_seed_t *seed);
bool mason_seed_write(wallet_seed_t *seed);

bool mason_bip32_generate_master_key_from_root_seed(
    crypto_curve_t curve_type,
    private_key_t *private_key,
    chaincode_t *chaincode);

bool mason_bip32_derive_keys(
    wallet_path_t *wallet_path,
    crypto_curve_t curve,
    private_key_t *private_key,
    chaincode_t *chaincode,
    extended_key_t *extended_key);
#endif
