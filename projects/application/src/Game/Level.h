#pragma once



namespace Game {
	class Level {
	public:
		virtual void Initialize() = 0;

		virtual void CreateLevel() = 0;
		virtual void UpdateLevel() = 0;
		virtual void DeleteLevel() = 0;

		virtual void Shutdown() = 0;
	};
}