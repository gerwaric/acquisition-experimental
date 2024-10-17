#pragma once

#include <acquisition/api_types/character.h>
#include <acquisition/api_types/stash_tab.h>
//#include <acquisition/data_stores/data_store.h>

#include <QObject>

#include <QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QVariant>

#include <vector>

class LeagueDataStore : public QObject {
    Q_OBJECT
public:
    LeagueDataStore(QObject *parent, const QString& data_directory);

    QStringList getCharacterList();
    QStringList getStashList();

    std::shared_ptr<poe_api::Character> getCharacter(const QString& character_id);
    std::shared_ptr<poe_api::StashTab> getStash(const QString& stash_id);

    std::vector<std::shared_ptr<poe_api::Character>> getCharacters();
    std::vector<std::shared_ptr<poe_api::StashTab>> getStashes();

    void storeCharacter(const poe_api::Character& character);
    void storeStash(const poe_api::StashTab& stash_tab);

public slots:

    void setUsername(const QString& username);
    void setLeague(const QString& league);

private:

    QString generateHash(const QString& data);

    QString m_data_directory;
    QString m_username;
    QString m_league;
    QSqlDatabase m_db;

};