#pragma once



namespace Nut
{


	class PerlinNoise
	{
	public:
		PerlinNoise();

	private:
		auto GetNoise(float x, float y) -> float;

	};


}
