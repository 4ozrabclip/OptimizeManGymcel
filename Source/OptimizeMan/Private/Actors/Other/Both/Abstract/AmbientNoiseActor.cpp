// Copyright © 2025 4ozStudio. All rights reserved.


#include "Actors/Other/Both/Abstract/AmbientNoiseActor.h"

#include "Actors/Characters/Player/PlayerCharacter_OM.h"
#include "Components/Audio/Abstract/GameAudio_OM.h"
#include "Game/Persistent/GameInstance_OM.h"
#include "Kismet/GameplayStatics.h"


AAmbientNoiseActor::AAmbientNoiseActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    MusicPlayer = CreateDefaultSubobject<UGameAudio_OM>(TEXT("MusicPlayer"));
    MusicPlayer->SetupAttachment(RootComponent);
    MusicPlayer->SetAudioType(EAudioTypes::MusicAudio);
    MusicPlayer->SetAutoActivate(false);
}

void AAmbientNoiseActor::BeginPlay()
{
    Super::BeginPlay();
    if (!MetaSound)
    {
        UE_LOG(LogTemp, Error, TEXT("NO METASOUND"));
        return;
    }
    
    MusicPlayer->SetSound(MetaSound);


    PlayMusic();
}

void AAmbientNoiseActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);


    
}

void AAmbientNoiseActor::PlayMusic()
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
        MusicToUse = &Songs_Cope;
        UE_LOG(LogTemp, Error, TEXT("Cope music"));
        break;
    case EPlayerEmotionalStates::Doomer:
        MusicToUse = &Songs_Cope;
        SetBiquadFilter(EBiquadFilterType::LowPass, 16000, 0.32f, 1.f);
        break;
    case EPlayerEmotionalStates::Gigachad:
        MusicToUse = &Songs_Cope;
        break;
    case EPlayerEmotionalStates::Grindset:
        MusicToUse = &Songs_Cope;

        break;
    case EPlayerEmotionalStates::GoblinMode:
        MusicToUse = &Songs_Goblin;

        TurnWaveShaperOnOff(true);
        break;
    default:
        MusicToUse = &Songs_Cope;
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
    MusicPlayer->OnAudioFinished.AddDynamic(this, &AAmbientNoiseActor::OnSongFinished);
    
}

void AAmbientNoiseActor::OnSongFinished()
{
    bMusicPlaying = false;
    if (MusicPlayer->CurrentVolumeMultiplier > 0.f) PlayMusic();
    //PlayGymMusic();
}


void AAmbientNoiseActor::SetBiquadFilter(EBiquadFilterType InType, const int InFrequency, const float InGain, const float InBandwidth)
{
    if (MusicPlayer)
    {
        MusicPlayer->SetIntParameter(TEXT("BiquadType"), static_cast<int32>(InType));
        MusicPlayer->SetIntParameter(TEXT("BiquadFrequency"), InFrequency);
        MusicPlayer->SetFloatParameter(TEXT("BiquadGain"), InGain);
        MusicPlayer->SetFloatParameter(TEXT("BiquadBandwidth"), InBandwidth);

    }
}
void AAmbientNoiseActor::TurnWaveShaperOnOff(const bool bWaveShaperOn)
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

void AAmbientNoiseActor::TurnEffectChannelOnOff(const bool bEffectChannelOn)
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
void AAmbientNoiseActor::ChangePitch(float InNewPitch)
{
    if (MusicPlayer)
    {
        MusicPlayer->SetFloatParameter(TEXT("PitchShift"), InNewPitch);
    }
}


void AAmbientNoiseActor::SetSong(USoundWave* InSong) const
{
    if (MusicPlayer && InSong)
    {
        MusicPlayer->SetWaveParameter(TEXT("AudioInput"), InSong);
    }
}
