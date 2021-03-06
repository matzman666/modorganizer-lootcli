#include "game_settings.h"

#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <boost/log/trivial.hpp>

namespace fs = boost::filesystem;

namespace loot {
	const std::set<std::string> GameSettings::oldDefaultBranches({
		"master",
		"v0.7",
		"v0.8",
	});

	GameSettings::GameSettings() : type_(GameType::tes4) {}

	GameSettings::GameSettings(const GameType gameCode, const std::string& folder) : type_(gameCode), repositoryBranch_("v0.10") {
		if (Type() == GameType::tes4) {
			name_ = "TES IV: Oblivion";
			registryKey_ = "Software\\Bethesda Softworks\\Oblivion\\Installed Path";
			lootFolderName_ = "Oblivion";
			masterFile_ = "Oblivion.esm";
			repositoryURL_ = "https://github.com/loot/oblivion.git";
		}
		else if (Type() == GameType::tes5) {
			name_ = "TES V: Skyrim";
			registryKey_ = "Software\\Bethesda Softworks\\Skyrim\\Installed Path";
			lootFolderName_ = "Skyrim";
			masterFile_ = "Skyrim.esm";
			repositoryURL_ = "https://github.com/loot/skyrim.git";
		}
		else if (Type() == GameType::tes5se) {
			name_ = "TES V: Skyrim Special Edition";
			registryKey_ = "Software\\Bethesda Softworks\\Skyrim Special Edition\\Installed Path";
			lootFolderName_ = "Skyrim Special Edition";
			masterFile_ = "Skyrim.esm";
			repositoryURL_ = "https://github.com/loot/skyrimse.git";
		}
		else if (Type() == GameType::fo3) {
			name_ = "Fallout 3";
			registryKey_ = "Software\\Bethesda Softworks\\Fallout3\\Installed Path";
			lootFolderName_ = "Fallout3";
			masterFile_ = "Fallout3.esm";
			repositoryURL_ = "https://github.com/loot/fallout3.git";
		}
		else if (Type() == GameType::fonv) {
			name_ = "Fallout: New Vegas";
			registryKey_ = "Software\\Bethesda Softworks\\FalloutNV\\Installed Path";
			lootFolderName_ = "FalloutNV";
			masterFile_ = "FalloutNV.esm";
			repositoryURL_ = "https://github.com/loot/falloutnv.git";
		}
		else if (Type() == GameType::fo4) {
			name_ = "Fallout 4";
			registryKey_ = "Software\\Bethesda Softworks\\Fallout4\\Installed Path";
			lootFolderName_ = "Fallout4";
			masterFile_ = "Fallout4.esm";
			repositoryURL_ = "https://github.com/loot/fallout4.git";
		}

		if (!folder.empty())
			lootFolderName_ = folder;
	}

	bool GameSettings::IsRepoBranchOldDefault() const {
		return oldDefaultBranches.count(repositoryBranch_) == 1;
	}

	bool GameSettings::operator == (const GameSettings& rhs) const {
		return (boost::iequals(name_, rhs.Name()) || boost::iequals(lootFolderName_, rhs.FolderName()));
	}

	GameType GameSettings::Type() const {
		return type_;
	}

	std::string GameSettings::Name() const {
		return name_;
	}

	std::string GameSettings::FolderName() const {
		return lootFolderName_;
	}

	std::string GameSettings::Master() const {
		return masterFile_;
	}

	std::string GameSettings::RegistryKey() const {
		return registryKey_;
	}

	std::string GameSettings::RepoURL() const {
		return repositoryURL_;
	}

	std::string GameSettings::RepoBranch() const {
		return repositoryBranch_;
	}

	fs::path GameSettings::GamePath() const {
		return gamePath_;
	}

	GameSettings& GameSettings::SetName(const std::string& name) {
		BOOST_LOG_TRIVIAL(trace) << "Setting \"" << name_ << "\" name to: " << name;
		name_ = name;
		return *this;
	}

	GameSettings& GameSettings::SetMaster(const std::string& masterFile) {
		BOOST_LOG_TRIVIAL(trace) << "Setting \"" << name_ << "\" master file to: " << masterFile;
		masterFile_ = masterFile;
		return *this;
	}

	GameSettings& GameSettings::SetRegistryKey(const std::string& registry) {
		BOOST_LOG_TRIVIAL(trace) << "Setting \"" << name_ << "\" registry key to: " << registry;
		registryKey_ = registry;
		return *this;
	}

	GameSettings& GameSettings::SetRepoURL(const std::string& repositoryURL) {
		BOOST_LOG_TRIVIAL(trace) << "Setting \"" << name_ << "\" repo URL to: " << repositoryURL;
		repositoryURL_ = repositoryURL;
		return *this;
	}

	GameSettings& GameSettings::SetRepoBranch(const std::string& repositoryBranch) {
		BOOST_LOG_TRIVIAL(trace) << "Setting \"" << name_ << "\" repo branch to: " << repositoryBranch;
		repositoryBranch_ = repositoryBranch;
		return *this;
	}

	GameSettings& GameSettings::SetGamePath(const boost::filesystem::path& path) {
		BOOST_LOG_TRIVIAL(trace) << "Setting \"" << name_ << "\" game path to: " << path;
		gamePath_ = path;
		return *this;
	}
}
