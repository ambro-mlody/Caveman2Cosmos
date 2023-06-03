#include "CvGameCoreDLL.h"
#include "CyArea.h"
#include "CyCity.h"
#include "CyPlot.h"

//
// published python interface for CyCity
//

void CyCityPythonInterface1(python::class_<CyCity>& x)
{
	OutputDebugString("Python Extension Module - CyCityPythonInterface1\n");
	x
		.def("kill", &CyCity::kill, "void () - kill the city")

		.def("getCityIndexPlot", &CyCity::getCityIndexPlot, python::return_value_policy<python::manage_new_object>(), "CyPlot* (int iIndex)")
		.def("canWork", &CyCity::canWork, "bool (CyPlot*) - can the city work the plot?")
		.def("countNumImprovedPlots", &CyCity::countNumImprovedPlots, "int ()")
		.def("countNumWaterPlots", &CyCity::countNumWaterPlots, "int ()")

		.def("findBaseYieldRateRank", &CyCity::findBaseYieldRateRank, "int (int /*YieldTypes*/ eYield)")
		.def("findYieldRateRank", &CyCity::findYieldRateRank, "int (int /*YieldTypes*/ eYield)")
		.def("findCommerceRateRank", &CyCity::findCommerceRateRank, "int (int /*CommerceTypes*/ eCommerce)")

		.def("canTrain", &CyCity::canTrain, "bool (int eUnit, bool bContinue, bool bTestVisible)")
		.def("canConstruct", &CyCity::canConstruct, "bool (int eBuilding, bool bContinue, bool bTestVisible, bool bIgnoreCost)")
		.def("canCreate", &CyCity::canCreate, "bool (int eProject, bool bContinue, bool bTestVisible)")
		.def("canMaintain", &CyCity::canMaintain, "bool (int eProcess)")
		.def("getFoodTurnsLeft", &CyCity::getFoodTurnsLeft, "int () - how many food turns remain?")
		.def("isProduction", &CyCity::isProduction, "bool () - is city producing?")
		.def("isProductionUnit", &CyCity::isProductionUnit, "bool () - is city training a unit?")
		.def("isProductionBuilding", &CyCity::isProductionBuilding, "bool () - is city constructing a building?")
		.def("isProductionProject", &CyCity::isProductionProject, "bool ()")
		.def("isProductionProcess", &CyCity::isProductionProcess, "bool () - is city maintaining a process?")

		.def("getProductionExperience", &CyCity::getProductionExperience, "int (int /*UnitTypes*/ eUnit)")
		.def("addProductionExperience", &CyCity::addProductionExperience, "void (CyUnit* pUnit, bool bConscript)")

		.def("getProductionUnit", &CyCity::getProductionUnit, "UnitID () - ID for unit that is being trained")
		.def("getProductionBuilding", &CyCity::getProductionBuilding, "BuildingID () - ID for building that is under construction")
		.def("getProductionProject", &CyCity::getProductionProject, "int /*ProjectTypes*/ ()")
		.def("getProductionProcess", &CyCity::getProductionProcess, "int /*ProcessTypes*/ ()")
		.def("getProductionName", &CyCity::getProductionName, "str () - description of item that the city is working on")
		.def("getGeneralProductionTurnsLeft", &CyCity::getGeneralProductionTurnsLeft, "int - # of production turns left for the top order node item in a city...")
		.def("getProductionNameKey", &CyCity::getProductionNameKey, "str () - description of item that the city is working on")
		.def("isFoodProduction", &CyCity::isFoodProduction, "bool () - is item under construction being created with food instead of production?")
		.def("getFirstUnitOrder", &CyCity::getFirstUnitOrder, "int (int /*UnitTypes*/ eUnit)")
		.def("getFirstBuildingOrder", &CyCity::getFirstBuildingOrder, "int (int /*BuildingTypes*/ eBuilding)")
		.def("getProductionProgress", &CyCity::getProductionProgress, "int () - returns the current production towards whatever is top of this city's OrderQueue")
		.def("getProductionNeeded", &CyCity::getProductionNeeded, "int () - # of production needed to complete construction")
		.def("getProductionTurnsLeft", &CyCity::getProductionTurnsLeft, "int () - # of turns remaining until item is completed")
		.def("getUnitProductionTurnsLeft", &CyCity::getUnitProductionTurnsLeft, "int (UnitID, int iNum) - # of turns remaining to complete UnitID")
		.def("getBuildingProductionTurnsLeft", &CyCity::getBuildingProductionTurnsLeft, "int (BuildingID, int iNum) - # of turns remaining to complete UnitID")
		.def("getProjectProductionTurnsLeft", &CyCity::getProjectProductionTurnsLeft, "int (int /*ProjectTypes*/ eProject, int iNum)")
		.def("setProductionProgress", &CyCity::setProductionProgress, "void (int iNewValue)")
		.def("changeProduction", &CyCity::changeProduction, "void (int iChange)")
		.def("getCurrentProductionDifference", &CyCity::getCurrentProductionDifference, "int (bool bIgnoreFood, bool bOverflow)")

		.def("canHurry", &CyCity::canHurry, "bool (HurryTypes eHurry, bool bTestVisible = 0) - can player eHurry in this city?")
		.def("getConscriptUnit", &CyCity::getConscriptUnit, "UnitID () - UnitID for the best unit the city can conscript")
		.def("flatConscriptAngerLength", &CyCity::flatConscriptAngerLength, "int ()")
		.def("canConscript", &CyCity::canConscript, "bool () - can the city conscript units?")
		.def("getBonusHealth", &CyCity::getBonusHealth, "int (BonusID) - total health bonus from BonusID")
		.def("getBonusHappiness", &CyCity::getBonusHappiness, "int (BonusID) - total happiness bonus from BonusID")
		.def("getBonusPower", &CyCity::getBonusPower, "int (int /*BonusTypes*/ eBonus)")
		.def("getBonusYieldRateModifier", &CyCity::getBonusYieldRateModifier, "int (int /*YieldTypes*/ eIndex, int /*BonusTypes*/ eBonus)")
		.def("getHandicapType", &CyCity::getHandicapType, "HandicapType () - owners difficulty level")
		.def("getCivilizationType", &CyCity::getCivilizationType, "CivilizationID () - owners CivilizationID")
		.def("getPersonalityType", &CyCity::getPersonalityType, "int /*LeaderHeadTypes*/ ()")
		.def("getArtStyleType", &CyCity::getArtStyleType, "int /*ArtStyleTypes*/ ()")

		.def("hasTrait", &CyCity::hasTrait, "bool (TraitID) - does owner have TraitID?")
		.def("isNPC", &CyCity::isNPC, "bool () - is owner an NPC?")
		.def("isHominid", &CyCity::isHominid, "bool () - is owner an Hominid?")
		.def("isHuman", &CyCity::isHuman, "bool () - is owner human?")
		.def("isVisible", &CyCity::isVisible, "bool (int /*TeamTypes*/ eTeam, bool bDebug)")

		.def("isCapital", &CyCity::isCapital, "bool () - is city the owners capital?")
		.def("isCoastal", &CyCity::isCoastal, "bool (int) - is the city on the coast?")
		.def("isDisorder", &CyCity::isDisorder, "bool () - is the city in disorder?")
		.def("isHolyCityByType", &CyCity::isHolyCityByType, "bool (ReligionID) - is the city ReligionID's holy city?")
		.def("isHolyCity", &CyCity::isHolyCity, "bool () - is the city ReligionID's holy city?")
		.def("isHeadquartersByType", &CyCity::isHeadquartersByType, "bool (CorporationID) - is the city CorporationID's headquarters?")
		.def("getNoMilitaryPercentAnger", &CyCity::getNoMilitaryPercentAnger, "int ()")
		.def("getWarWearinessPercentAnger", &CyCity::getWarWearinessPercentAnger, "int ()")
		.def("unhappyLevel", &CyCity::unhappyLevel, "int (int iExtra)")
		.def("happyLevel", &CyCity::happyLevel, "int ()")
		.def("angryPopulation", &CyCity::angryPopulation, "int (iExtra) - # of unhappy citizens")
		.def("totalFreeSpecialists", &CyCity::totalFreeSpecialists)
		.def("goodHealth", &CyCity::goodHealth, "int () - total health")
		.def("badHealth", &CyCity::badHealth, "int (bool bNoAngry) - total unhealthiness")
		.def("healthRate", &CyCity::healthRate, "int (bool bNoAngry, int iExtra)")
		.def("foodConsumption", &CyCity::foodConsumption, "int (bool bNoAngry, int iExtra)")
		.def("foodDifference", &CyCity::foodDifference, "int (bool bBottom) - result of getYieldRate(Food) - foodConsumption()")
		.def("growthThreshold", &CyCity::growthThreshold, "int () - value needed for growth")
		.def("productionLeft", &CyCity::productionLeft, "int () - result of (getProductionNeeded() - getProductionProgress()")
		.def("getHurryGold", &CyCity::getHurryGold, "int (HurryID) - total value of gold when hurrying")
		.def("hurryPopulation", &CyCity::hurryPopulation, "int (HurryID) - value of each pop when hurrying")
		.def("hurryProduction", &CyCity::hurryProduction, "int (HurryID)")
		.def("flatHurryAngerLength", &CyCity::flatHurryAngerLength, "int ()")

		.def("isFreeBuilding", &CyCity::isFreeBuilding, "bool (BuildingID)")
		.def("getID", &CyCity::getID, "int () - index ID # for the city - use with pPlayer.getCity(ID) to obtain city instance")
		.def("getX", &CyCity::getX, "int () - X coordinate for the cities plot")
		.def("getY", &CyCity::getY, "int () - Y coordinate for the cities plot")
		.def("plot", &CyCity::plot, python::return_value_policy<python::manage_new_object>(), "CyPlot () - returns cities plot instance")
		.def("isConnectedTo", &CyCity::isConnectedTo, "bool (CyCity*) - is city connected to CyCity* via the Trade Network?")
		.def("isConnectedToCapital", &CyCity::isConnectedToCapital, "bool (iOwner) - connected to the capital?")
		.def("area", &CyCity::area, python::return_value_policy<python::manage_new_object>(), "CyArea() () - returns CyArea instance for location of city")
		.def("waterArea", &CyCity::waterArea, python::return_value_policy<python::manage_new_object>(), "CyArea* ()")
		.def("getRallyPlot", &CyCity::getRallyPlot, python::return_value_policy<python::manage_new_object>(), "CyPlot () - returns city's rally plot instance")
		.def("getGameTurnFounded", &CyCity::getGameTurnFounded, "int () - GameTurn the city was founded")

		.def("getGameTurnAcquired", &CyCity::getGameTurnAcquired, "int ()")
		.def("getPopulation", &CyCity::getPopulation, "int () - total city population")
		.def("setPopulation", &CyCity::setPopulation, "void (int iNewValue) - sets the city population to iNewValue")
		.def("changePopulation", &CyCity::changePopulation, "void (int iChange) - adjusts the city population by iChange")
		.def("getRealPopulation", &CyCity::getRealPopulation, "int () - total city population in \"real\" numbers")
		.def("getHighestPopulation", &CyCity::getHighestPopulation, "int () ")
		.def("setHighestPopulation", &CyCity::setHighestPopulation, "void (iNewValue)")
		.def("getWorkingPopulation", &CyCity::getWorkingPopulation, "int () - # of citizens who are working")
		.def("getSpecialistPopulation", &CyCity::getSpecialistPopulation, "int () - # of specialists")
		.def("getNumGreatPeople", &CyCity::getNumGreatPeople, "int () - # of great people who are joined to the city")
		.def("getBaseGreatPeopleRate", &CyCity::getBaseGreatPeopleRate, "int () - base great person rate")
		.def("getGreatPeopleRate", &CyCity::getGreatPeopleRate, "int () - total Great Person rate")
		.def("changeBaseGreatPeopleRate", &CyCity::changeBaseGreatPeopleRate)
		.def("getGreatPeopleProgress", &CyCity::getGreatPeopleProgress, "int () - current great person progress")
		.def("getGreatPeopleRateModifier", &CyCity::getGreatPeopleRateModifier, "int ()")

		.def("getNumWorldWonders", &CyCity::getNumWorldWonders, "int ()")
		.def("getNumNationalWonders", &CyCity::getNumNationalWonders, "int ()")
		.def("getMaxNumWorldWonders", &CyCity::getMaxNumWorldWonders, "int ()")
		.def("getMaxNumNationalWonders", &CyCity::getMaxNumNationalWonders, "int ()")
		.def("getNumBuildings", &CyCity::getNumBuildings, "int ()")
		.def("changeGreatPeopleProgress", &CyCity::changeGreatPeopleProgress, "void (int iChange) - adjusts great person progress by iChange")
		.def("isGovernmentCenter", &CyCity::isGovernmentCenter, "bool () - is city the government center?")

		.def("getMaintenance", &CyCity::getMaintenance, "int () - cities current maintenance cost")
		.def("getMaintenanceTimes100", &CyCity::getMaintenanceTimes100, "int () - cities current maintenance cost")
		.def("calculateDistanceMaintenance", &CyCity::calculateDistanceMaintenance, "int ()")
		.def("calculateNumCitiesMaintenance", &CyCity::calculateNumCitiesMaintenance, "int ()")
		.def("calculateColonyMaintenanceTimes100", &CyCity::calculateColonyMaintenanceTimes100, "int ()")
		.def("getMaintenanceModifier", &CyCity::getMaintenanceModifier, "int () - total value of the city maintenance modifier")
		.def("getWarWearinessModifier", &CyCity::getWarWearinessModifier)

		.def("getEspionageHealthCounter", &CyCity::getEspionageHealthCounter, "int ()")
		.def("changeEspionageHealthCounter", &CyCity::changeEspionageHealthCounter, "void (int iChange)")
		.def("getEspionageHappinessCounter", &CyCity::getEspionageHappinessCounter, "int ()")
		.def("changeEspionageHappinessCounter", &CyCity::changeEspionageHappinessCounter, "void (int iChange)")

		.def("getBuildingHealth", &CyCity::getBuildingHealth, "int (int eBuilding)")

		.def("getMilitaryHappinessUnits", &CyCity::getMilitaryHappinessUnits, "number of military units creating happiness")
		.def("getBuildingHappiness", &CyCity::getBuildingHappiness, "int (int eBuilding)")
		.def("getReligionHappiness", &CyCity::getReligionHappiness, "int (int eReligion)")
		.def("getExtraHappiness", &CyCity::getExtraHappiness, "int ()")
		.def("getExtraHealth", &CyCity::getExtraHealth, "int ()")
		.def("changeExtraHealth", &CyCity::changeExtraHealth, "void (int iChange)")
		.def("changeExtraHappiness", &CyCity::changeExtraHappiness, "void (int iChange)")
		.def("getHurryAngerTimer", &CyCity::getHurryAngerTimer, "int () - Anger caused by Hurrying timer")
		.def("changeHurryAngerTimer", &CyCity::changeHurryAngerTimer, "void (iChange) - adjust Hurry Angry timer by iChange")
		.def("getConscriptAngerTimer", &CyCity::getConscriptAngerTimer, "int () - returns the amount of time left on the conscript anger timer")
		.def("changeConscriptAngerTimer", &CyCity::changeConscriptAngerTimer, "void (int iChange) -changes the amount of time left on the conscript anger timer")
		.def("getDefyResolutionAngerTimer", &CyCity::getDefyResolutionAngerTimer, "int () - returns the amount of time left on the anger timer")
		.def("changeDefyResolutionAngerTimer", &CyCity::changeDefyResolutionAngerTimer, "void (int iChange) -changes the amount of time left on the anger timer")
		.def("flatDefyResolutionAngerLength", &CyCity::flatDefyResolutionAngerLength, "int ()")
		.def("getHappinessTimer", &CyCity::getHappinessTimer, "int () - Temporary Happiness timer")
		.def("changeHappinessTimer", &CyCity::changeHappinessTimer, "void (iChange) - adjust Happiness timer by iChange")
		.def("isNoUnhappiness", &CyCity::isNoUnhappiness, "bool () - is the city unaffected by unhappiness?")
		.def("isBuildingOnlyHealthy", &CyCity::isBuildingOnlyHealthy, "bool () - is the city ?")

		.def("getFood", &CyCity::getFood, "int () - stored food")
		.def("setFood", &CyCity::setFood, "void (iNewValue) - set stored food to iNewValue")
		.def("changeFood", &CyCity::changeFood, "void (iChange) - adjust stored food by iChange")
		.def("getFoodKept", &CyCity::getFoodKept, "int ()")
		.def("getMaxProductionOverflow", &CyCity::getMaxProductionOverflow, "int () - value of max overflow production")
		.def("getOverflowProduction", &CyCity::getOverflowProduction, "int () - value of overflow production")
		.def("setOverflowProduction", &CyCity::setOverflowProduction, "void (iNewValue) - set overflow production to iNewValue")
		.def("getFeatureProduction", &CyCity::getFeatureProduction, "int () - value of feature production")
		.def("setFeatureProduction", &CyCity::setFeatureProduction, "void (iNewValue) - set feature production to iNewValue")
		.def("getMilitaryProductionModifier", &CyCity::getMilitaryProductionModifier, "int () - value of adjustments to military production")
		.def("getSpaceProductionModifier", &CyCity::getSpaceProductionModifier, "int ()")
		.def("getExtraTradeRoutes", &CyCity::getExtraTradeRoutes, "int () - returns the number of extra trade routes this city has")
		.def("getMaxTradeRoutes", &CyCity::getMaxTradeRoutes, "int () - returns the number of extra trade routes this city has")
		.def("changeExtraTradeRoutes", &CyCity::changeExtraTradeRoutes, "void (iChange) - Change the number of trade routes this city has")
		.def("getTradeRouteModifier", &CyCity::getTradeRouteModifier, "int ()")
		.def("getForeignTradeRouteModifier", &CyCity::getForeignTradeRouteModifier, "int ()")
		.def("getBuildingDefense", &CyCity::getBuildingDefense, "int () - building defense")
		.def("getFreeExperience", &CyCity::getFreeExperience, "int () - # of free experience newly trained units receive")
		.def("getMaxAirlift", &CyCity::getMaxAirlift, "int ()")
		.def("getAirModifier", &CyCity::getAirModifier, "int () - returns the air defense modifier")
		.def("getNukeModifier", &CyCity::getNukeModifier, "int ()")
		.def("isPower", &CyCity::isPower, "bool ()")
		.def("getDefenseDamage", &CyCity::getDefenseDamage, "int () - value of damage city defenses can receive")
		.def("changeDefenseDamage", &CyCity::changeDefenseDamage, "void (iChange) - adjust damage value by iChange")
		.def("getNaturalDefense", &CyCity::getNaturalDefense, "int ()")
		.def("getTotalDefense", &CyCity::getTotalDefense, "int (bool bIgnoreBuilding)")
		.def("getDefenseModifier", &CyCity::getDefenseModifier, "int (bool bIgnoreBuilding)")

		.def("getOccupationTimer", &CyCity::getOccupationTimer, "int () - total # of turns remaining on occupation timer")
		.def("isOccupation", &CyCity::isOccupation, "bool () - is the city under occupation?")
		.def("setOccupationTimer", &CyCity::setOccupationTimer, "void (iNewValue) - set the Occupation Timer to iNewValue")
		.def("changeOccupationTimer", &CyCity::changeOccupationTimer, "void (iChange) - adjusts the Occupation Timer by iChange")
		.def("isNeverLost", &CyCity::isNeverLost, "bool ()")
		.def("setNeverLost", &CyCity::setNeverLost, "void (iNewValue)")
		.def("isBombarded", &CyCity::isBombarded, "bool ()")
		.def("setBombarded", &CyCity::setBombarded, "void (iNewValue)")
		.def("isDrafted", &CyCity::isDrafted, "bool ()")
		.def("setDrafted", &CyCity::setDrafted, "void (iNewValue)")
		.def("isAirliftTargeted", &CyCity::isAirliftTargeted, "bool ()")
		.def("setAirliftTargeted", &CyCity::setAirliftTargeted, "void (iNewValue)")
		.def("isCitizensAutomated", &CyCity::isCitizensAutomated, "bool () - are citizens under automation?")
		.def("setCitizensAutomated", &CyCity::setCitizensAutomated, "void (bool bNewValue) - set city animation bNewValue")
		.def("isProductionAutomated", &CyCity::isProductionAutomated, "bool () - is production under automation?")
		.def("setProductionAutomated", &CyCity::setProductionAutomated, "void (bool bNewValue) - set city production automation to bNewValue")
		.def("isWallOverride", &CyCity::isWallOverride, "bool isWallOverride()")
		.def("setWallOverride", &CyCity::setWallOverride, "setWallOverride(bool bOverride)")
		.def("isPlundered", &CyCity::isPlundered, "bool ()")
		.def("setPlundered", &CyCity::setPlundered, "void (iNewValue)")
		.def("getOwner", &CyCity::getOwner, "int /*PlayerTypes*/ ()")
		.def("getTeam", &CyCity::getTeam, "int /*TeamTypes*/ ()")
		.def("getPreviousOwner", &CyCity::getPreviousOwner, "int /*PlayerTypes*/ ()")
		.def("getOriginalOwner", &CyCity::getOriginalOwner, "int /*PlayerTypes*/ ()")
		.def("setOriginalOwner", &CyCity::setOriginalOwner, "void (int /*PlayerTypes*/)")
		.def("getCultureLevel", &CyCity::getCultureLevel, "int /*CultureLevelTypes*/ ()")
		.def("getCultureThreshold", &CyCity::getCultureThreshold)

		.def("getPlotYield", &CyCity::getPlotYield, "int (int /*YieldTypes*/) - base rate for YieldType")
		.def("getBaseYieldRateModifier", &CyCity::getBaseYieldRateModifier)
		.def("getYieldRate", &CyCity::getYieldRate, "int (int /*YieldTypes*/) - total value of YieldType")
		.def("getYieldRateModifier", &CyCity::getYieldRateModifier, "int (int /*YieldTypes*/) - yield rate modifier for YieldType")
		.def("getTradeYield", &CyCity::getTradeYield, "int (int /*YieldTypes*/) - trade adjustment to YieldType")

		.def("isEventOccured", &CyCity::isEventOccured, "bool (int /*EventTypes*/)")
	;
}
