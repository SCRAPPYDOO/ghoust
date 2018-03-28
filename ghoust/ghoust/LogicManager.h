#pragma once

class LogicManager
{
	public:
		static LogicManager* getInstance();
		~LogicManager();

	private:
		LogicManager();
		static LogicManager* logicManager;
};
