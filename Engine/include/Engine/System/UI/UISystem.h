#pragma once

#include "Engine/System/System.h"

#include <vector>
#include <memory>

class UserInterface;

class UISystem : public System
{
public:
	UISystem();
	~UISystem();
	void onUpdate(double i_dt_s) override;
	void addActiveUserInterface(UserInterface* i_ui);
	std::vector<UserInterface*>& getActiveUserInterface();
	bool removeActiveUserInterface(UserInterface* i_ui);

	template<typename T, typename... Args>
	T& createUserInterface(Args&&... i_args) {
		static_assert(std::is_base_of_v<UserInterface, T>,
			"T must derive from UserInterface");
		auto ui = std::make_unique<T>(std::forward<Args>(i_args)...);
		T& ref = *ui;
		m_created_ui_list.push_back(std::move(ui));
		return ref;
	}
protected:
private:
	std::vector<UserInterface*> m_active_ui_list;
	std::vector<std::unique_ptr<UserInterface>> m_created_ui_list;
};

