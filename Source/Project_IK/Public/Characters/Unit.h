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
#include "Interfaces/Damageable.h"
#include "Interfaces/UnitInterface.h"

#include "Unit.generated.h"
class UHitPointsUI;
class UObjectPoolComponent;
class UWidgetComponent;
class UCharacterStatComponent;
class UCrowdControlComponent;
class UDamageUI;
enum class EHeroEvent : uint8;


DECLARE_DELEGATE_RetVal_OneParam(FDamageData, FOnDamage, FDamageData);

UCLASS()
class PROJECT_IK_API AUnit : public ACharacter, public IDamageable, public IUnitInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AUnit();
	const UCharacterStatComponent* GetCharacterStat() const;
	FVector GetForwardDir() const;
	void SetForwardDir(const FVector& Forward_Dir);
	
	UFUNCTION(BlueprintCallable)
	virtual void GetDamage(FDamageData data) override;

	UFUNCTION(BlueprintCallable)
	void Heal(float heal);

	UFUNCTION(BlueprintCallable)
	void ApplyBuff(FBuff buff);

	UFUNCTION(BlueprintCallable)
	bool RemoveBuff(FName BuffName);

	UFUNCTION(BlueprintCallable)
	void ApplyCrowdControl(ECCType cc_type, float duration);
	
	UFUNCTION()
	virtual void GetStunned(float stun_duration) override;

	UFUNCTION()
	virtual void OnStunned() override;

	UFUNCTION()
	virtual void FinishStun() override;

	template<typename T, typename FuncType>
	void BindDamageEvent(EHeroEvent bound_event, T* object, FuncType callback);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UHitPointsUI> hp_UI_class_;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void Die() override;

	void SetDamageUI(FDamageData data, bool is_evaded);
	FTransform GetActorTransformForDamageUI() const noexcept;

	void GetDamageByDot(FDamageData data);
	void GetDamageByPEM(FDamageData data);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true", BindWidget))
	UCharacterStatComponent* character_stat_component_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Unit")
	UCrowdControlComponent* cc_component_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true", BindWidget))
	UAnimMontage* stun_montage_;

	//TODO: 오직 Stun의 테스트를 위해 사용한다. 적절한 애니메이션을 찾으면 바로 삭제해야 한다!
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true", BindWidget))
	UMaterial* original_material;
	
	//TODO: 오직 Stun의 테스트를 위해 사용한다. 적절한 애니메이션을 찾으면 바로 삭제해야 한다!
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true", BindWidget))
	UMaterial* test_stun_material_;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true", BindWidget))
	UWidgetComponent* hp_UI_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true", BindWidget))
	FVector forward_dir_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true", BindWidget))
	UAnimMontage* stunned_montage_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageUI", meta = (AllowPrivateAccess = "true"))
	UObjectPoolComponent* object_pool_component_;

	UPROPERTY(Transient)
	FTimerHandle stun_timer_;

	TMap<EHeroEvent, TArray<FOnDamage>> dmg_event_map_;
};

template<typename T, typename FuncType>
inline void AUnit::BindDamageEvent(EHeroEvent bound_event, T* object, FuncType callback)
{
	TArray<FOnDamage>& delegate_array = dmg_event_map_.FindOrAdd(bound_event);

	delegate_array.AddDefaulted();
	delegate_array.Last().BindUObject(object, callback);
}
