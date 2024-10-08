// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/GameModes/MainGameModeBase.h"
#include "EatCoinGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AEatCoinGameMode : public AMainGameModeBase
{
	GENERATED_BODY()

public:

    AEatCoinGameMode();

    // 부스트 아이템 지속 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    float BoostDuration = 10.0f;

    // 부스트 아이템 습득 시 증가 속도 (2배)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    float SpeedMultiplier = 2.0f;

    // 부스트와 오버랩 됐을 때 속도 증가 반영
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void ApplySpeedBoost(ACharacter* PlayerCharacter);

    // 코인과 오버랩 됐을 때 점수 반영
    void AddCoinScoreRule(APlayerState* PlayerState, int32 ScoreAmount);

    virtual void PostLogin(APlayerController* NewPlayer) override;

    virtual void HandleGameStart() override;

    virtual void HandleRoundEnd() override;

    // 게임 종료 후 레벨 이동
    void HandleServerTravel();

    // 서버 트래블 타이머 핸들러
    FTimerHandle ServerTravelTimerHandle;

   // EatCoin 게임시작까지 남은 시간 카운트다운
    void SetECGameStartCountdownRule();

    // 다음 라운드로 전환하는 함수
    virtual void TransitionToNextRound() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Eat Coin Game Rules", meta = (AllowPrivateAccess = "true"))
    int32 ECGameStartCountdownTimeInSeconds;

    UPROPERTY()
    TSubclassOf<class AEatCoinGameMode> StartEatCoinGameMode;

protected:
    virtual void BeginPlay() override;

    // 라운드 전환 타이머 핸들러
    FTimerHandle RoundTransitionTimerHandle;

    // EC 게임 카운트다운 타이머 핸들러
    FTimerHandle ECGameCountdownTimerHandle;

private:
    // 부스트 지속시간 타이머 핸들러
    FTimerHandle BoostTimerHandle;

    // 부스트가 적용된 상태인지 체크
    bool bIsBoostActive = false;

    // 기본 속도(BP_ThirdPerson Max Walk Speed 참고)
    float OriginalSpeed = 500.0f;
};
