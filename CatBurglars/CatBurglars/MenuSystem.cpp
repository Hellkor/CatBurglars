#include "MenuSystem.h"



MenuSystem::MenuSystem() { mActivePage = nullptr; }

void MenuSystem::addPage(MenuPage *page) {
	Pages.push_back(page);
}

void MenuSystem::setPage(std::string name) {
	if (mActivePage != nullptr) {
		mActivePage->resetPage();
	}
	for each(MenuPage *page in Pages) {
		if (page->getName() == name) {
			mActivePage = page;
			mActivePage->resetPage();
		}
	}
}

void MenuSystem::render(sf::RenderWindow *window) {
	if (mActivePage != nullptr) {
		mActivePage->render(window);
	}
}
void MenuSystem::UpdateNavigation() {
	if (mActivePage != nullptr) {
		mActivePage->UpdatedMenuNavigation();
	}
}