/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.19.2024
Summary : Source file for an actor that holds damage UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/DamageUI.h"

#include "Components/WidgetComponent.h"
#include "UI/DamageWidget.h"

// Sets default values
ADamageUI::ADamageUI()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	widget_component_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	SetRootComponent(widget_component_);
	widget_component_->SetWidgetSpace(EWidgetSpace::Screen);
	widget_component_->SetDrawSize(FVector2D(100.0));

	initial_velocity_ = FVector(20.f, 0.f, 50.f);
	velocity_ = initial_velocity_;
	gravity_ = FVector(0.f, 0.f, -98.f);

	time_to_live_ = 0.75f;
}

void ADamageUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	velocity_ += gravity_ * DeltaTime;

	FVector location = GetActorLocation();
	location += velocity_ * DeltaTime;
	SetActorLocation(location);
}

void ADamageUI::SetHealAmount(float HealAmount)
{
	if (widget_component_)
	{
		UDamageWidget* widget = Cast<UDamageWidget>(widget_component_->GetWidget());
		if (widget)
		{
			widget->SetColorAndOpacity(FLinearColor(0.f, 1.f, 0.f));
			widget->SetDamageAmount(HealAmount);
		}
	}
}

void ADamageUI::SetDamageAmount(float DamageAmount, FLinearColor Color)
{
	if (widget_component_)
	{
		UDamageWidget* widget = Cast<UDamageWidget>(widget_component_->GetWidget());
		if (widget)
		{
			widget->SetColorAndOpacity(Color);
			widget->SetDamageAmount(DamageAmount);
		}
	}
}

void ADamageUI::SetMissed()
{
	if (widget_component_)
	{
		UDamageWidget* widget = Cast<UDamageWidget>(widget_component_->GetWidget());
		if (widget)
		{
			widget->SetMissed();
		}
	}
}

void ADamageUI::SetInUse(bool in_use)
{
	Super::SetInUse(in_use);
	velocity_ = initial_velocity_;
}

// Called when the game starts or when spawned
void ADamageUI::BeginPlay()
{
	Super::BeginPlay();
	if (damage_widget_class_)
	{
		UUserWidget* widget = CreateWidget<UDamageWidget>(GetWorld(), damage_widget_class_);
		widget_component_->SetWidget(widget);
	}
}

