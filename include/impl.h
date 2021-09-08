#pragma once
#include "bar_serving.h"
#include <functional>
#include <map>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    int i = 0;
    const std::array<BeerBrand, 6> recipe = { BeerBrand::HoeGaarden, BeerBrand::Corona, BeerBrand::Carlsberg, BeerBrand::Bud, BeerBrand::ZlataPraha, BeerBrand::Leffe};
    const BeerBrand& operator()()
    {
        return recipe[ (i++)%recipe.size() ];
    }
};


/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer( BeerBrand beer )
{
    return ( beer == BeerBrand::HoeGaarden || beer == BeerBrand::Corona );
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = []( BeerBrand first, BeerBrand second )
{
    return  getBeerCountry( first ) == getBeerCountry( second );
};

struct MixingPolicy
{
    static const std::map<std::pair< AlcoholDrink, NonAlcoholDrink>, Cocktail > recipe;
    
    /**
     * @todo Implement static transformator function
     * @return crafted cocktail
     *
     * @note Cookbook:
     * Gin + Lime juice = Gimlet;
     * Gin + Grapefruit juice = Greyhount;
     * Whiskey + SevenUp = SevenPlusSeven;
     * Others + Others = Oops;
     */
    static Cocktail mix( const AlcoholDrink & first, const NonAlcoholDrink & second )
    {
        auto key = std::make_pair(first,second);
        return ( recipe.count( key ) ? recipe.at( key ) : Cocktail::Oops ); 
    }
};

std::function<Cocktail(const AlcoholDrink &, const NonAlcoholDrink &)> mixer {&MixingPolicy::mix};
