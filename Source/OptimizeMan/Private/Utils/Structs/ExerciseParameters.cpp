#include "Utils/Structs/ExerciseParameters.h"

#include "Utils/UtilityHelpers_OMG.h"
#include "Utils/Structs/PlayerData_Gymcel.h"


void FExerciseParameters::UpdateParameters(UGameInstance_OMG* GameInstance)
{
	if (!GameInstance) return;

	FBodyStatus& BodyStatus = GameInstance->GetBodyStatus();

	if (BodyStatus.bCurrentlyOnSteroids)
	{
		LowerBodyIncrease = 0.09f;
		ArmIncrease = 0.09f;
		ShoulderIncrease = 0.09;
	}
}
