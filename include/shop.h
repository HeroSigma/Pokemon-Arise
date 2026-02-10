#ifndef GUARD_SHOP_H
#define GUARD_SHOP_H

#include "global.h"

extern struct ItemSlot gMartPurchaseHistory[3];

void CreatePokemartMenu(const u16 *itemsForSale);
void CreateDecorationShop1Menu(const u16 *itemsForSale);
void CreateDecorationShop2Menu(const u16 *itemsForSale);
void CreateStoreMenu(const u16 *itemsForSale);
void CreateDirectBuyMenu(const u16 *itemsForSale);
void CB2_InitBuyMenu(void);
void CB2_ExitSellMenu(void);

#endif // GUARD_SHOP_H
