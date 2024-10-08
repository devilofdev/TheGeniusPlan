
#include "ChatComponent.h"
#include "TheGeniusPlan/Widget/ChatWidget.h"
#include "TheGeniusPlan/Widget/ChatEntryBoxWidget.h"
#include "GameFramework/GameState.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "ChatRoomActor.h"


UChatComponent::UChatComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	bIsChatVaild = false;

	static ConstructorHelpers::FClassFinder<UChatWidget> ChatClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ChatSystem/Widget/ChatWidget.ChatWidget_C'"));

	if (ChatClass.Succeeded())
	{
		ChatWidgetClass = ChatClass.Class;
	}
	else
	{
	}

	ChatWidget = nullptr;

}


void UChatComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UChatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UChatComponent::CreateChatWidget(uint8 RoomType)
{
	if(!ChatWidgetClass)
	{
		return;
	}

	if (ChatWidget != nullptr)
	{
		ChatWidget->AddToViewport();
		ChatWidget->ChatRoomType = RoomType;
	}
	else
	{
		ChatWidget = Cast<UChatWidget>(CreateWidget(GetWorld(), ChatWidgetClass));
		ChatWidget->AddToViewport();
		ChatWidget->ChatRoomType = RoomType;
	}

	bIsChatVaild = true;

}

void UChatComponent::RemoveChatWidget()
{
	if (ChatWidget)
	{
		ChatWidget->RemoveFromParent();
		ChatWidget->ClearChatWidget();
	}

	bIsChatVaild = false;
}

bool UChatComponent::GetChatVaild()
{
	return bIsChatVaild;
}

void UChatComponent::AddMyChatMessage_Implementation(const FString& Message, uint8 Type)
{
	if(ChatWidget)
	{
		ChatWidget->AddMyChatMessage(Message, Type);
	}
}

void UChatComponent::SendMyMessage_Implementation(const FString& Message, uint8 Type)
{
	UWorld* World = GetWorld();

	if (World)
	{

		AGameStateBase* GameStateBase = World->GetGameState();

		if (GameStateBase)
		{

			TArray<APlayerState*> PlayerStateArray = GameStateBase->PlayerArray;

			for(APlayerState* PlayerState : PlayerStateArray)
			{
				UChatComponent* UserChatComponent = PlayerState->GetOwningController()->GetComponentByClass<UChatComponent>();

				UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerState->GetFName().ToString());

				if (UserChatComponent)
				{
					UserChatComponent->AddMyChatMessage(Message, Type);
				}
			}
		}
	}

}

