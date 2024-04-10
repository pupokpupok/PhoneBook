
#ifndef EXAMPLE_POSTGRESQL_USERDB_HPP
#define EXAMPLE_POSTGRESQL_USERDB_HPP

#include "dto/ContactsDto.hpp"
#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * UserDb client definitions.
 */
class ContactsDb : public oatpp::orm::DbClient {
public:

  ContactsDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
  {

    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
    // TODO - Add more migrations here.
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = executor->getSchemaVersion();
    OATPP_LOGD("ContactsDb", "Migration - OK. Version=%d.", version);

  }

  QUERY(createContacts,
        "INSERT INTO contacts"
        "(id, phone, name, address) VALUES "
        "(:contacts.id, :contacts.phone, :contacts.name, :contacts.address)"
        "RETURNING *;",
        PREPARE(true),
        PARAM(oatpp::Object<ContactsDto>, contacts))

  QUERY(updateContacts,
        "UPDATE contacts "
        "SET "
        " phone=:contacts.phone, "
        " name=:contacts.name, "
        " address=:contacts.address "
        "WHERE "
        " id=:contacts.id "
        "RETURNING *;",
        PREPARE(true), 
        PARAM(oatpp::Object<ContactsDto>, contacts))

  QUERY(getContactsById,
        "SELECT * FROM contacts WHERE id=:id;",
        PREPARE(true), 
        PARAM(oatpp::Int32, id))

  QUERY(getAllContacts,
        "SELECT * FROM contacts LIMIT :limit OFFSET :offset;",
        PREPARE(true), 
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit))

  QUERY(deleteContactsById,
        "DELETE FROM contacts WHERE id=:id;",
        PREPARE(true), 
        PARAM(oatpp::Int32, id))

};

#include OATPP_CODEGEN_END(DbClient) 

#endif 
