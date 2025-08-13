return {
    {
        id = "wood_axe",
        name = "Wood Axe",
        tag = "Tool",
        properties = {
            rarity = "Common",
            durability = 10,
            damage = nil,
            defense = nil,
            can_collect = "wood",
            health_refill = nil,
            stamina_refill = nil,
            hunger_refill = nil,
            thirst_refill = nil,
        },

        crafting = {
            required_items = {
                { id = "wood", quantity = 6}
            }
        }
    },

    {
        id = "wood_pickaxe",
        name = "Wood Pickaxe",
        tag = "Tool",
        properties = {
            rarity = "Common",
            durability = 10,
            damage = nil,
            defense = nil,
            can_collect = "stone",
            health_refill = nil,
            stamina_refill = nil,
            hunger_refill = nil,
            thirst_refill = nil,
        },

        crafting = {
            required_items = {
                { id = "wood", quantity = 6}
            }
        }
    },
}
