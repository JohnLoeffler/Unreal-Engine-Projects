#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blockbreaker.h"
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
  /** The Number of bricks in the level, not counting empty space or indestructible materials */
  UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Level|Grid|Data")
    int32 BricksInLevel;
  /** The Highest Value in the Color pattern */
  UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Level|Grid|Colors")
    float HighValue;
  /** The Lowest Value in the Color pattern */
  UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Level|Grid|Colors")
    float LowValue;
  /** The Width of the Grid */
  UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Level|Grid|Dimensions")
    int32 Width;
  /** The Height of the Grid */
  UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Level|Grid|Dimensions")
    int32 Height;
  /** The Color Palette for the Grid */
  UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Level|Grid|Colors")
    TArray<FVector> Palette;
  /** The Color Pattern for the Grid */
  UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Level|Grid|Pattern")
    TArray<float> ColorPattern;
  /** The BrickType Pattern for the Grid */
  UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Level|Grid|Pattern")
    TArray<int32> BrickTypes;
  /** The Color Pattern for the Grid */
  UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Level|Grid|Pattern")
    TArray<int32> SpecialTypes;
};
