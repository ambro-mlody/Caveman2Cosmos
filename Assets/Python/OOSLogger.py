# OOS logger: writes the info contained in the sync checksum to a log file
from CvPythonExtensions import CyGlobalContext, YieldTypes, CommerceTypes, UnitAITypes


def writeLog():
	import SystemPaths as SP
	import CvUtil
	GC = CyGlobalContext()
	MAP = GC.getMap()
	GAME = GC.getGame()
	iPlayer = GAME.getActivePlayer()
	szName = CvUtil.convertToStr(GC.getActivePlayer().getName())
	szName = SP.logDir + "\\%s - Player %d - Turn %d OOSLog.txt" % (szName, iPlayer, GAME.getGameTurn())
	pFile = open(szName, "w")

	SEP = "-----------------------------------------------------------------\n"

	# Backup current language
	iLanguage = GAME.getCurrentLanguage()
	# Force english language for logs
	GAME.setCurrentLanguage(0)

	# Global data
	pFile.write(2 * SEP + "\tGLOBALS\n" + 2 * SEP + "\n")

	pFile.write("Last MapRand Value: %d\n" % GAME.getMapRand().getSeed())
	pFile.write("Last SorenRand Value: %d\n" % GAME.getSorenRand().getSeed())

	pFile.write("Total num cities: %d\n" % GAME.getNumCities())
	pFile.write("Total population: %d\n" % GAME.getTotalPopulation())
	pFile.write("Total Deals: %d\n" % GAME.getNumDeals())

	pFile.write("Total owned plots: %d\n" % MAP.getOwnedPlots())
	pFile.write("Total num areas: %d\n\n\n" % MAP.getNumAreas())

	# Player data
	for iPlayer in xrange(GC.getMAX_PLAYERS()):
		CyPlayer = GC.getPlayer(iPlayer)
		if CyPlayer.isEverAlive():

			pFile.write(2 * SEP + "%s player %d: %s\n" % (['NPC', 'Human'][CyPlayer.isHuman()], iPlayer, CvUtil.convertToStr(CyPlayer.getName())))
			pFile.write("  Civilization: %s\n" % CvUtil.convertToStr(CyPlayer.getCivilizationDescriptionKey()))
			pFile.write("  Alive: %s\n" % CyPlayer.isAlive())

			pFile.write(2 * SEP + "\n\nBasic data:\n-----------\n")

			pFile.write("Player %d Score: %d\n" % (iPlayer, GAME.getPlayerScore(iPlayer)))
			pFile.write("Player %d Population: %d\n" % (iPlayer, CyPlayer.getTotalPopulation()))
			pFile.write("Player %d Total Land: %d\n" % (iPlayer, CyPlayer.getTotalLand()))
			pFile.write("Player %d Greater Gold: %d Gold: %d\n" % (iPlayer, CyPlayer.getGreaterGold(), CyPlayer.getGold()))
			pFile.write("Player %d Assets: %d\n" % (iPlayer, CyPlayer.getAssets()))
			pFile.write("Player %d Power: %d\n" % (iPlayer, CyPlayer.getPower()))
			pFile.write("Player %d Num Cities: %d\n" % (iPlayer, CyPlayer.getNumCities()))
			pFile.write("Player %d Num Units: %d\n" % (iPlayer, CyPlayer.getNumUnits()))
			pFile.write("Player %d Num Selection Groups: %d\n" % (iPlayer, CyPlayer.getNumSelectionGroups()))
			pFile.write("Player %d Difficulty: %d\n" % (iPlayer, CyPlayer.getHandicapType()))
			pFile.write("Player %d State Religion: %s\n" % (iPlayer, CvUtil.convertToStr(CyPlayer.getStateReligionKey())))
			pFile.write("Player %d Total Culture: %d\n" % (iPlayer, CyPlayer.countTotalCulture()))

			pFile.write("\n\nYields:\n-------\n")

			for iYield in xrange(YieldTypes.NUM_YIELD_TYPES):
				pFile.write("Player %d %s Total Yield: %d\n" % (iPlayer, CvUtil.convertToStr(GC.getYieldInfo(iYield).getDescription()), CyPlayer.calculateTotalYield(iYield)))

			pFile.write("\n\nCommerce:\n---------\n")

			for iCommerce in xrange(CommerceTypes.NUM_COMMERCE_TYPES):
				pFile.write("Player %d %s Total Commerce: %d\n" % (iPlayer, CvUtil.convertToStr(GC.getCommerceInfo(iCommerce).getDescription()), CyPlayer.getCommerceRate(CommerceTypes(iCommerce))))

			pFile.write("\n\nBonus Info:\n-----------\n")

			for iBonus in xrange(GC.getNumBonusInfos()):
				szTemp = CvUtil.convertToStr(GC.getBonusInfo(iBonus).getDescription())
				pFile.write("Player %d, %s, Number Available: %d\n" % (iPlayer, szTemp, CyPlayer.getNumAvailableBonuses(iBonus)))
				pFile.write("Player %d, %s, Import: %d\n" % (iPlayer, szTemp, CyPlayer.getBonusImport(iBonus)))
				pFile.write("Player %d, %s, Export: %d\n\n" % (iPlayer, szTemp, CyPlayer.getBonusExport(iBonus)))

			pFile.write("\n\nImprovement Info:\n-----------------\n")

			for iImprovement in xrange(GC.getNumImprovementInfos()):
				pFile.write("Player %d, %s, Improvement count: %d\n" % (iPlayer, CvUtil.convertToStr(GC.getImprovementInfo(iImprovement).getDescription()), CyPlayer.getImprovementCount(iImprovement)))

			pFile.write("\n\nBuilding Info:\n--------------------\n")

			for iBuildingClass in xrange(GC.getNumBuildingClassInfos()):
				pFile.write("Player %d, %s, Building class count plus making: %d\n" % (iPlayer, CvUtil.convertToStr(GC.getBuildingClassInfo(iBuildingClass).getDescription()), CyPlayer.getBuildingClassCountPlusMaking(iBuildingClass)))

			pFile.write("\n\nUnit Class Info:\n--------------------\n")

			for iUnitClass in xrange(GC.getNumUnitClassInfos()):
				pFile.write("Player %d, %s, Unit class count plus training: %d\n" % (iPlayer, CvUtil.convertToStr(GC.getUnitClassInfo(iUnitClass).getDescription()), CyPlayer.getUnitClassCountPlusMaking(iUnitClass)))

			pFile.write("\n\nUnitAI Types Info:\n------------------\n")

			for iUnitAIType in xrange(int(UnitAITypes.NUM_UNITAI_TYPES)):
				pFile.write("Player %d, %s, Unit AI Type count: %d\n" % (iPlayer, GC.getUnitAIInfo(iUnitAIType).getDescription(), CyPlayer.AI_totalUnitAIs(UnitAITypes(iUnitAIType))))

			pFile.write("\n\nCity Info:\n----------")

			if CyPlayer.getNumCities():
				CyCity, i = CyPlayer.firstCity(False)
				while CyCity:
					pFile.write(
						"\nX: %d, Y: %d\nFounded: %d\nPopulation: %d\nBuildings: %d\nImproved Plots: %d\nProducing: %s (%d Hammers invested)\n%d Tiles Worked, %d Specialists\n\
						Great People (GP)\n  %d Settled GP\n  GP Progress: %d\n  GP Base Rate: %d\n  GP Rate: %d\n"
						% (
							CyCity.getX(), CyCity.getY(), CyCity.getGameTurnFounded(), CyCity.getPopulation(), CyCity.getNumBuildings(), CyCity.countNumImprovedPlots(),
							CvUtil.convertToStr(CyCity.getProductionName()), CyCity.getProduction(), CyCity.getWorkingPopulation(), CyCity.getSpecialistPopulation(),
							CyCity.getNumGreatPeople(), CyCity.getGreatPeopleProgress(), CyCity.getBaseGreatPeopleRate(), CyCity.getGreatPeopleRate()
						)
					);
					CyCity, i = CyPlayer.nextCity(i, False)
			else:
				pFile.write("\nNo Cities")

			pFile.write("\n\nUnit Info:\n----------")

			if CyPlayer.getNumUnits():
				CyUnit, i = CyPlayer.firstUnit(False)
				while CyUnit:
					pFile.write("\nPlayer %d, Unit ID: %d, %s\n" % (iPlayer, CyUnit.getID(), CvUtil.convertToStr(CyUnit.getName())))
					pFile.write("X: %d, Y: %d\nDamage: %d\n" % (CyUnit.getX(), CyUnit.getY(), CyUnit.getDamage()))
					pFile.write("Experience: %d\nLevel: %d\n" % (CyUnit.getExperience(), CyUnit.getLevel()))
					bFirst = True
					for j in xrange(GC.getNumPromotionInfos()):
						if CyUnit.isHasPromotion(j):
							if bFirst:
								pFile.write("Promotions:\n")
								bFirst = False
							pFile.write("\t" + CvUtil.convertToStr(GC.getPromotionInfo(j).getDescription()) + "\n")
					bFirst = True
					for j in xrange(GC.getNumUnitCombatInfos()):
						if CyUnit.isHasUnitCombat(j):
							if bFirst:
								pFile.write("UnitCombats:\n")
								bFirst = False
							pFile.write("\t" + CvUtil.convertToStr(GC.getUnitCombatInfo(j).getDescription()) + "\n")

					CyUnit, i = CyPlayer.nextUnit(i, False)
			else:
				pFile.write("\nNo Units")
			# Space at end of player's info
			pFile.write("\n\n")
	# Close file
	pFile.close()

	# Restore current language
	GAME.setCurrentLanguage(iLanguage)
