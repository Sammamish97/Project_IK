/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Header file for unit. Every object which have status should inherit this class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Attackable.h"
#include "Interfaces/Damageable.h"
#include "Interfaces/UnitInterface.h"
#include "Unit.generated.h"

class UDisplayDataAsset;
class UHitPointsUI;
class UObjectPoolComponent;
class UWidgetComponent;
class UCharacterStatComponent;
class UCrowdControlComponent;
class ADamageUI;
class UDelegateBridgeSubsystem;
class UOutlineComponent;
enum class EUnitEvent : uint8;
struct FBuffStatusData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnitEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnApplyBuffDelegate, EBuffType, buff_type, UDisplayDataAsset*, buff_data, bool, is_permanant, float, duration);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuffExpired, EBuffType, buff_type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFinishAction, UBehaviorTreeComponent*, bt_component, bool, is_interrupted);


UCLASS(Abstract)
class PROJECT_IK_API AUnit : public ACharacter, public IAttackable, public IDamageable, public IUnitInterface
{
	GENERATED_BODY()
	friend UDelegateBridgeSubsystem;
public:
	// Sets default values for this character's properties
	AUnit();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	virtual void Die() override;
	
	FVector GetForwardDir() const;
	void SetForwardDir(const FVector& Forward_Dir);

	void SetAttackTarget(AActor* target);
	AActor* GetAttackTarget();

	virtual void SetUnitStateWithInterrupt(EUnitState type);
	virtual void ResetUnitState();

	void SetOutlineState(EOutlineState state);

	virtual void Attack(AActor* target) override;

	UFUNCTION(BlueprintCallable)
	ECharacterType GetCharacterType() const;
	UCharacterStatComponent* GetCharacterStat();
	UCrowdControlComponent* GetCCComponent();
	UWidgetComponent* GetHPUIWidgetComponent();
	EUnitBoneType GetBoneType() const;
	bool IsHero() const;

	void FinishAction();
	
	UFUNCTION(BlueprintCallable)
	virtual void GetDamage(FDamageData data) override;
	
	UFUNCTION(BlueprintCallable)
	void Heal(float heal);
	
	UFUNCTION(BlueprintCallable)
	virtual void ApplyStatusBuff(EBuffType buff_type, FBuffStatusData buff_status);
	virtual void AddBuffUI(EBuffType type, UDisplayDataAsset* ui_data);
	virtual void AddBuffUI(EBuffType type, UDisplayDataAsset* ui_data, float duration_);
	virtual void RemoveBuffUI(EBuffType type);

	UFUNCTION(BlueprintCallable)
	virtual void RemoveBuff(EBuffType buff_type);

	UFUNCTION(BlueprintCallable)
	void ApplyCrowdControl(ECCType cc_type, float duration);

	void AcquireShield(float ShieldAmount, float Duration);
	
	UFUNCTION()
	virtual void GetStunned(float stun_duration) override;

	UFUNCTION()
	virtual void OnStunned() override;

	UFUNCTION()
	virtual void FinishStun() override;

	UFUNCTION()
	virtual void OnEnterBattleOnce();
	
	float GetPitchDiffBetweenTarget();
	
	UFUNCTION()
	void DispatchUnitEvent(EUnitEvent type);

protected:
	void SetDamageUI(FDamageData data, bool is_evaded);

	ADamageUI* SpawnDamageUI();

	void GetDamageByDot(FDamageData data);
	void GetDamageByPEM(FDamageData data);
	void GetDamageByMagic(FDamageData data);
	void RecoverAttackerByLifeSteal(FDamageData data);

protected:
	//Name/Character Type/Bone Type은 BP에서 초기화 되는것을 기대한다.
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	FName character_name_;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	ECharacterType character_type_;

public:
	UPROPERTY()
	FOnBuffExpired OnBuffExpired;

	UPROPERTY()
	FOnApplyBuffDelegate OnApplyBuff;
	
	UPROPERTY()
	FOnFinishAction OnFinishAction;

//HP UI
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	TSubclassOf<UUserWidget> hp_UI_class_;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> hp_widget_component_;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterStatComponent> character_stat_component_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Unit")
	TObjectPtr<UCrowdControlComponent> cc_component_;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> stun_montage_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> stunned_montage_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageUI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UObjectPoolComponent> dmg_ui_object_pool_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Unit")
	TObjectPtr<UOutlineComponent> outline_component_;

	UPROPERTY(EditDefaultsOnly, Category = "Unit", meta = (AllowPrivateAccess = "true"))
	EAIFindTargetType ai_find_target_type_;
	
	UPROPERTY(EditDefaultsOnly, Category = "Unit", meta = (AllowPrivateAccess = "true"))
	FVector forward_dir_;

	UPROPERTY(EditDefaultsOnly, Category = "Unit", meta = (AllowPrivateAccess = "true"))
	bool is_hero_ = false;
	
	UPROPERTY(Transient)
	FTimerHandle stun_timer_;

	UPROPERTY()
	TMap<EUnitEvent, FOnUnitEvent> on_unit_event_;
	
	bool is_first_attack_ = true;
	
	float capsule_half_height_ = 0.f;
	float capsule_radius_ = 0.f;
};