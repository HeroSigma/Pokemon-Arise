#ifndef GUARD_ONLINE_STORE_H
#define GUARD_ONLINE_STORE_H

#include "global.h"
#include "constants/items.h"

#define MAX_CART_ITEMS 20
#define MAX_ITEM_QUANTITY 999
#define STORE_NUM_CATEGORIES 7

// Store Categories
enum
{
    STORE_CATEGORY_ITEMS,
    STORE_CATEGORY_MEDICINE,
    STORE_CATEGORY_BALLS,
    STORE_CATEGORY_BATTLE_ITEMS,
    STORE_CATEGORY_TRAINING_ITEMS,
    STORE_CATEGORY_FORM_CHANGING_ITEMS,
    STORE_CATEGORY_TMS,
    STORE_CATEGORY_COUNT = STORE_NUM_CATEGORIES
};

// Store States
enum
{
    STORE_STATE_INIT,
    STORE_STATE_CATEGORY_SELECT,
    STORE_STATE_ITEM_LIST,
    STORE_STATE_ITEM_ACTION_MENU,
    STORE_STATE_QUANTITY_SELECT,
    STORE_STATE_CART_VIEW,
    STORE_STATE_PURCHASE_CONFIRM,
    STORE_STATE_PURCHASE_COMPLETE,
    STORE_STATE_SCHEDULE_VIEW,
    STORE_STATE_EXIT
};

// Store Actions
enum
{
    STORE_ACTION_BUY_SINGLE,
    STORE_ACTION_ADD_TO_CART,
    STORE_ACTION_VIEW_CART,
    STORE_ACTION_CHECKOUT,
    STORE_ACTION_CANCEL
};

// Confirmation Types
enum
{
    CONFIRM_TYPE_PURCHASE,
    CONFIRM_TYPE_ADD_TO_CART,
    CONFIRM_TYPE_CHECKOUT
};

struct StoreCartItem
{
    u16 itemId;
    u16 quantity;
};

struct OnlineStoreData
{
    u8 state;
    u8 currentCategory;
    u8 selectedItemIndex;
    u8 selectedActionIndex;
    u8 scrollOffset;
    // Per-category state for better UX
    u8 selectedIndexByCat[STORE_NUM_CATEGORIES];
    u8 scrollOffsetByCat[STORE_NUM_CATEGORIES];
    u8 cartSize;
    u16 selectedQuantity;
    bool8 isViewingCart;
    bool8 needsRefresh;
    u8 confirmationType;  // 0=purchase, 1=add_to_cart, 2=checkout
    u8 confirmationChoice; // 0=YES, 1=NO
    // Optional sale state
    bool8 saleActive;
    u8 salePercent; // 0-100
    struct StoreCartItem cart[MAX_CART_ITEMS];
};

// Function declarations
void CB2_OnlineStore(void);
void InitOnlineStore(void);
void UpdateStoreDisplay(void);
void DrawStoreInterface(void);
void ShowCartContents(void);

// Helper functions
bool8 AddItemToCart(u16 itemId, u16 quantity);
bool8 RemoveItemFromCart(u16 itemId, u16 quantity);
void ClearCart(void);
u32 GetCartTotalCost(void);
bool8 IsCartEmpty(void);
const u16 *GetStoreCategoryItems(u8 category);
u16 GetStoreCategoryItemCount(u8 category);
const u8 *GetStoreCategoryName(u8 category);
bool8 PurchaseCartItems(void);
bool8 PurchaseSingleItem(u16 itemId, u16 quantity);
u32 GetStoreItemPrice(u16 itemId);

// Sale controls
void OnlineStore_SetSale(bool8 active, u8 percent);
bool8 OnlineStore_IsSaleActive(void);

// Main store callbacks
void CB2_OnlineStore(void);
void Task_OnlineStore(u8 taskId);

#endif // GUARD_ONLINE_STORE_H
