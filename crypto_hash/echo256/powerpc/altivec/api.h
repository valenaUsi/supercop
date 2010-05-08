/*------------------------------------------------------------------------------------ */
/* Implementation of the double pipe ECHO hash function in its 256-bit outputs variant.*/
/* Optimized for PowerPC with Altivec                                                  */
/*                                                                                     */
/* Date:     2010-04-12                                                                */
/*                                                                                     */
/* Authors:  Ryad Benadjila  <ryadbenadjila@gmail.com>                                 */
/*           Olivier Billet  <billet@eurecom.fr>                                       */
/*------------------------------------------------------------------------------------ */
#define CRYPTO_BYTES 32
#define CRYPTO_VERSION "2.0"
