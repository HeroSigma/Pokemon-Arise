#ifndef GUARD_CONFIG_ONLINE_STORE_H
#define GUARD_CONFIG_ONLINE_STORE_H

// Online Store global configuration
#define ONLINE_STORE_ENABLED      FALSE   // Master switch for the online store feature
#define ONLINE_STORE_SURCHARGE    0       // Percentage surcharge applied to all prices

// Context availability
#define ONLINE_STORE_LINK         TRUE    // Allow purchases while in link mode
#define ONLINE_STORE_BATTLE       TRUE    // Allow purchases during battles
#define ONLINE_STORE_SAFARI       TRUE    // Allow purchases inside the Safari Zone

// Category toggles
#define ONLINE_STORE_CATEGORY_ITEMS        TRUE
#define ONLINE_STORE_CATEGORY_MEDICINE     TRUE
#define ONLINE_STORE_CATEGORY_BATTLE_ITEMS TRUE
#define ONLINE_STORE_CATEGORY_BALLS        TRUE
#define ONLINE_STORE_CATEGORY_TMHM         TRUE
#define ONLINE_STORE_CATEGORY_BERRIES      TRUE
#define ONLINE_STORE_CATEGORY_KEY_ITEMS    TRUE

#endif // GUARD_CONFIG_ONLINE_STORE_H
