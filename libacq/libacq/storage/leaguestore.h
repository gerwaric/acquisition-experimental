#pragma once

#include <libacq/poe/character.h>
#include <libacq/poe/stashtab.h>

#include <QObject>

#include <QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QVariant>

class LeagueStore : public QObject {
    Q_OBJECT
public:
    LeagueStore(const QString& directory, QObject *parent);

    QStringList getCharacterList();
    QStringList getStashList();

    std::unique_ptr<poe_api::Character> getCharacter(const QString& character_id);
    std::unique_ptr<poe_api::StashTab> getStash(const QString& stash_id);

    poe_api::CharacterList getCharacters();
    poe_api::StashTabList getStashes();

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
