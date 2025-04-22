#include "Utils/Structs/ExerciseParameters.h"

#include "Utils/GameInstance_OM.h"

void FExerciseParameters::UpdateParameters(UGameInstance_OM* GameInstance)
{
	if (!GameInstance) return;

	FPlayerData& PlayerData = GameInstance->GetPlayerData();

	if (PlayerData.bCurrentlyOnSteroids)
	{
		LowerBodyIncrease = 0.09f;
		ArmIncrease = 0.09f;
		ShoulderIncrease = 0.09;
	}
}
