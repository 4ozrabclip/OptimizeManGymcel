// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Gym/Concrete/GymSpeaker_OM.h"
#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/AudioComponent.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Utils/Structs/AudioTypes.h"
#include "Utils/Structs/PlayerData.h"

// Sets default values
AGymSpeaker_OM::AGymSpeaker_OM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	MusicPlayer = CreateDefaultSubobject<UGameAudio_OM>(TEXT("MusicPlayer"));
	MusicPlayer->SetupAttachment(RootComponent);
    MusicPlayer->SetAudioType(EAudioTypes::MusicAudio);
    MusicPlayer->SetAutoActivate(false);
    
}

void AGymSpeaker_OM::BeginPlay()
{
	Super::BeginPlay();

    if (!MetaSound)
    {
        UE_LOG(LogTemp, Error, TEXT("NO METASOUND"));
        return;
    }
    
    MusicPlayer->SetSound(MetaSound);

    TurnEffectChannelOnOff(true);
    
    SetActorTickEnabled(true);

    PlayGymMusic();
    
}
void AGymSpeaker_OM::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!Player) return;
    if (Player->GetCurrentPlayMode() == EPlayModes::WorkoutMode)
    {
        if (Player->GetIsDoingRep())
        {
            if (CurrentBiquadFrequency > 400)
            {
                CurrentBiquadFrequency -= DeltaSeconds * 3000;
                SetBiquadFilter(EBiquadFilterType::LowPass, CurrentBiquadFrequency, 0.4f, 1.f);
            }
        }
        else
        {
            if (CurrentBiquadFrequency < 20000)
            {
                CurrentBiquadFrequency += DeltaSeconds * 3000;
                SetBiquadFilter(EBiquadFilterType::LowPass, CurrentBiquadFrequency, 0.4f, 1.f);
            }
        }
    }
    else if (Player->GetCurrentPlayMode() == EPlayModes::SocialMode)
    {
        if (CurrentBiquadFrequency > 600)
        {
            CurrentBiquadFrequency -= DeltaSeconds * 3000;
            SetBiquadFilter(EBiquadFilterType::LowPass, CurrentBiquadFrequency, 0.4f, 1.f);
        }
    }
    else if (CurrentBiquadFrequency < 20000)
    {
        CurrentBiquadFrequency += DeltaSeconds * 3000;
        SetBiquadFilter(EBiquadFilterType::LowPass, CurrentBiquadFrequency, 0.4f, 1.f);
    }

    
}

void AGymSpeaker_OM::PlayGymMusic()
{
    if (bMusicPlaying) return;
    
    if (!MusicPlayer)
    {
        UE_LOG(LogTemp, Error, TEXT("Music player component on gymspeaker is null"));
        return;
    }
    
    if (!Player)
        Player = Cast<APlayerCharacter_OM>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    
    if (!GameInstance)
        GameInstance = Cast<UGameInstance_OM>(GetWorld()->GetGameInstance());
    
    if (!Player)
    {
        UE_LOG(LogTemp, Error, TEXT("Player is null"));
        return;
    }
    
    EPlayerEmotionalStates CurrentEmotionalState = GameInstance->GetCurrentEmotionalState();
    

    TArray<USoundWave*>* MusicToUse = nullptr;
    
    switch (CurrentEmotionalState)
    {
    case EPlayerEmotionalStates::Cope:
        MusicToUse = &GymSongs;
        UE_LOG(LogTemp, Error, TEXT("Cope music"));
        break;
    case EPlayerEmotionalStates::Doomer:
        MusicToUse = &GymSongs;
        UE_LOG(LogTemp, Error, TEXT("doomer music 1"));
        SetBiquadFilter(EBiquadFilterType::LowPass, 16000, 0.32f, 1.f);
        UE_LOG(LogTemp, Error, TEXT("doomer music 2"));
        break;
    case EPlayerEmotionalStates::Gigachad:
        MusicToUse = &GymSongs;
        UE_LOG(LogTemp, Error, TEXT("chad music 1"));
        break;
    case EPlayerEmotionalStates::Grindset:
        MusicToUse = &GymSongs;
        UE_LOG(LogTemp, Error, TEXT("grind music 1"));
        break;
    case EPlayerEmotionalStates::GoblinMode:
        MusicToUse = &GymSongs_Goblin;
        UE_LOG(LogTemp, Error, TEXT("goblin music 1"));
        TurnWaveShaperOnOff(true);
        break;
    default:
        MusicToUse = &GymSongs;
        UE_LOG(LogTemp, Error, TEXT("default music 1"));
        break;
    }
    if (!MusicToUse || MusicToUse->Num() <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("No music to use"));
        return;
    }
    
    const int RandomSongIndex = FMath::RandRange(0, MusicToUse->Num() - 1);
    
    if (!MusicToUse->IsValidIndex(RandomSongIndex))
    {
        UE_LOG(LogTemp, Warning, TEXT("RandomSongIndex %d is invalid. Array size: %d"), RandomSongIndex, MusicToUse->Num());
        return;
    }

    if (!(*MusicToUse)[RandomSongIndex])
    {
        UE_LOG(LogTemp, Warning, TEXT("Sound at index %d is null"), RandomSongIndex);
        return;
    }
    
    SetSong((*MusicToUse)[RandomSongIndex]);
    MusicPlayer->Play();

    bMusicPlaying = true;

   
    MusicPlayer->OnAudioFinished.RemoveAll(this);
    MusicPlayer->OnAudioFinished.AddDynamic(this, &AGymSpeaker_OM::OnGymSongFinished);
    
}

void AGymSpeaker_OM::OnGymSongFinished()
{
    bMusicPlaying = false;
    if (MusicPlayer->CurrentVolumeMultiplier > 0.f) PlayGymMusic();
    //PlayGymMusic();
}


void AGymSpeaker_OM::SetBiquadFilter(EBiquadFilterType InType, const int InFrequency, const float InGain, const float InBandwidth)
{
    if (MusicPlayer)
    {
        MusicPlayer->SetIntParameter(TEXT("BiquadType"), static_cast<int32>(InType));
        MusicPlayer->SetIntParameter(TEXT("BiquadFrequency"), InFrequency);
        MusicPlayer->SetFloatParameter(TEXT("BiquadGain"), InGain);
        MusicPlayer->SetFloatParameter(TEXT("BiquadBandwidth"), InBandwidth);

    }
}
void AGymSpeaker_OM::TurnWaveShaperOnOff(const bool bWaveShaperOn)
{
    if (MusicPlayer)
    {
        if (bWaveShaperOn)
        {
            MusicPlayer->SetBoolParameter(TEXT("bWaveShaperOn"), true);
            MusicPlayer->SetBoolParameter(TEXT("bMainChannelOn"), false);
            MusicPlayer->SetBoolParameter(TEXT("bEffectChannelOn"), false);
        }
        else
        {
            MusicPlayer->SetBoolParameter(TEXT("bWaveShaperOn"), false);
            MusicPlayer->SetBoolParameter(TEXT("bMainChannelOn"), false);
            MusicPlayer->SetBoolParameter(TEXT("bEffectChannelOn"), true);
        }
        
    }
}

void AGymSpeaker_OM::TurnEffectChannelOnOff(const bool bEffectChannelOn)
{
    if (MusicPlayer)
    {
        if (bEffectChannelOn)
        {
            MusicPlayer->SetBoolParameter(TEXT("bEffectChannelOn"), true);
            MusicPlayer->SetBoolParameter(TEXT("bMainChannelOn"), false);
            MusicPlayer->SetBoolParameter(TEXT("bEffectChannelOff"), false);
        }
        else
        {
            MusicPlayer->SetBoolParameter(TEXT("bEffectChannelOn"), false);
            MusicPlayer->SetBoolParameter(TEXT("bMainChannelOn"), true);
            MusicPlayer->SetBoolParameter(TEXT("bEffectChannelOff"), false);
        }

    }
}
void AGymSpeaker_OM::ChangePitch(float InNewPitch)
{
    if (MusicPlayer)
    {
        MusicPlayer->SetFloatParameter(TEXT("PitchShift"), InNewPitch);
    }
}


void AGymSpeaker_OM::SetSong(USoundWave* InSong) const
{
    if (MusicPlayer && InSong)
    {
        MusicPlayer->SetWaveParameter(TEXT("AudioInput"), InSong);
    }
}
