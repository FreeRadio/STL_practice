#include "impl.h"


    /**
     * @note Cookbook:
     * Gin + Lime juice = Gimlet;
     * Gin + Grapefruit juice = Greyhount;
     * Whiskey + SevenUp = SevenPlusSeven;
     * Others + Others = Oops;
     */
const std::map<std::pair< AlcoholDrink, NonAlcoholDrink>, Cocktail > MixingPolicy::recipe = {
    {{ AlcoholDrink::Gin,     NonAlcoholDrink::LimeJuice},          Cocktail::Gimlet},
    {{ AlcoholDrink::Gin,     NonAlcoholDrink::GrapefruitJuice},    Cocktail::Greyhount},
    {{ AlcoholDrink::Whiskey, NonAlcoholDrink::SevenUp},            Cocktail::SevenPlusSeven},
};