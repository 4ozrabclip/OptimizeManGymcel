#include "Utils/Structs/ExerciseParameters.h"

#include "Game/Persistent/GameInstance_OM.h"

void FExerciseParameters::UpdateParameters(UGameInstance_OM* GameInstance)
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
