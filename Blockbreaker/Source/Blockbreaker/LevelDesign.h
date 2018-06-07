#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelDesign.generated.h"

class ULevelPalette;
class ULevelPattern;
UCLASS()
class BLOCKBREAKER_API ULevelDesign : public UObject
{
  GENERATED_BODY()
public:
  ULevelDesign();
  virtual ~ULevelDesign() {}

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level|Grid|Dimensions")
    int32 Width;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level|Grid|Dimensions")
    int32 Height;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level|Grid|Colors")
    TArray<FVector> Palette;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level|Grid|Pattern")
    TArray<float> Pattern;
};
