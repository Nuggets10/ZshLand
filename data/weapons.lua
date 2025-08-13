return {
    {
        id = "wood_sword",
        name = "Wood Sword",
        tag = "Weapon",
        properties = {
            rarity = "Common",
            durability = 10,
            damage = 3,
            defense = nil,
            can_collect = nil,
            health_refill = nil,
            stamina_refill = nil,
            hunger_refill = nil,
            thirst_refill = nil,
        },

        crafting = {
            required_items = {
                { id = "wood", quantity = 4}
            }
        }
    },

    {
        id = "wood_mace",
        name = "Wood Mace",
        tag = "Weapon",
        properties = {
            rarity = "Common",
            durability = 16,
            damage = 6,
            defense = nil,
            can_collect = nil,
            health_refill = nil,
            stamina_refill = nil,
            hunger_refill = nil,
            thirst_refill = nil,
        },

        crafting = {
            required_items = {
                { id = "wood", quantity = 8}
            }
        }
    },
}
