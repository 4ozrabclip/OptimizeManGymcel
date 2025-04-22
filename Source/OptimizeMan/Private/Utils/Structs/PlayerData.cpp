
#include "Utils/Structs/PlayerData.h"

void FPlayerData::SetEnergy(const float InEnergy, const bool bGoingToSleep)
{
	if (Energy < 0.f && !bGoingToSleep)
	{
		return;
	}
	//If going to sleep, are setting the energy fully
	if (bGoingToSleep)
	{
		Energy = InEnergy;
	}
	else //If not going to sleep, are adding the energy on
	{
		Energy += InEnergy;
	}
}
