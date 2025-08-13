return {
    {
        id = "apple",
        name = "Apple",
        tag = "Consumable",
        properties = {
            rarity = "Common",
            durability = nil,
            damage = nil,
            defense = nil,
            can_collect = nil,
            health_refill = 1,
            stamina_refill = 0,
            hunger_refill = 5,
            thirst_refill = 2,
        },

        crafting = {
            required_items = {
            }
        }
    },

    {
        id = "bread",
        name = "Bread",
        tag = "Consumable",
        properties = {
            rarity = "Common",
            durability = nil,
            damage = nil,
            defense = nil,
            can_collect = nil,
            health_refill = 1,
            stamina_refill = 0,
            hunger_refill = 5,
            thirst_refill = 2,
        },

        crafting = {
            required_items = {
                { id = "wheat", quantity = 3 }
            }
        }
    }
}
