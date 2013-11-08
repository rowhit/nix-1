// Copyright (c) 2013, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#include "TestProperty.hpp"

void TestProperty::setUp() {
    f1 = new File("test_block.h5", FileMode::ReadWrite);
}

void TestProperty::tearDown() {
    delete f1;
}

void TestProperty::testAddRemoveValue() {
    Section s = f1->createSection("PropertyTest", "test");

    if (s.hasPropertyByName("TestProperty")) {
        s.removeProperty(s.getPropertyByName("TestProperty").id());
    }
    Property p = s.addProperty("TestProperty");

    stringstream msg;
    msg << "Error while getting property name!";
    CPPUNIT_ASSERT_MESSAGE(msg.str(), p.name().compare("TestProperty") == 0 );

    stringstream msg1;
    msg1 << "Error getting value count. Should have been 0!";
    CPPUNIT_ASSERT_MESSAGE(msg1.str(), p.valueCount() == 0 );

    std::string str = "This is a  test string.";
    std::string str2 = "a reference";
    std::string str3 = "a file name";
    p.addValue(str,0.0, str2, str3);

    stringstream msg2;
    msg2 << "Error getting value count. Should have been 1!";
    CPPUNIT_ASSERT_MESSAGE(msg2.str(), p.valueCount() == 1 );

    p.removeValues();

    stringstream msg3;
    msg3 << "Error setting property name. Should have been refused since property has values!";
    CPPUNIT_ASSERT_MESSAGE(msg3.str(), p.valueCount() == 0 );

    f1->removeSection(s.id());
}

void TestProperty::testAccessingValues() {
    Section s = f1->createSection("PropertyTest", "test");
    if (s.hasPropertyByName("TestProperty")) {
        s.removeProperty(s.getPropertyByName("TestProperty").id());
    }
    Property p = s.addProperty("TestProperty");
    std::string str = "This is a test string.";
    std::string str2 = "a reference";
    std::string str3 = "a file name";
    std::string str4 = "a common encoder";
    std::string str5 = "the checksum";

    p.addValue(str, 0.0, str2, str3, str4, str5);

    StringValue val;
    p.value(0, val);
    stringstream valmsg;
    valmsg << "Error accessing string value! Error accessing field value!";
    string test(val.value);
    CPPUNIT_ASSERT_MESSAGE(valmsg.str(), test.compare(str) == 0);

    stringstream refmsg;
    refmsg << "Error accessing string value! Error accessing field reference!";
    test.assign(val.reference);
    CPPUNIT_ASSERT_MESSAGE(refmsg.str(), test.compare(str2) == 0);

    stringstream filemsg;
    filemsg << "Error accessing string value! Error accessing filename!";
    test.assign(val.filename);
    CPPUNIT_ASSERT_MESSAGE(filemsg.str(), test.compare(str3) == 0);

    stringstream encmsg;
    encmsg << "Error accessing string value! Error accessing field encoder!";
    test.assign(val.encoder);
    CPPUNIT_ASSERT_MESSAGE(encmsg.str(), test.compare(str4) == 0);

    stringstream chkmsg;
    chkmsg << "Error accessing string value! Error accessing field checksum!";
    test.assign(val.checksum);
    CPPUNIT_ASSERT_MESSAGE(chkmsg.str(), test.compare(str5) == 0);
    /*
   string value(p.value(0));
   stringstream msg2;
   msg2 << "Error accessing string value!";
   CPPUNIT_ASSERT_MESSAGE(msg2.str(), value.compare("This is a test string.") == 0);

   stringstream msg3;
   msg3
   << "Error accessing string value with index larger than value count. Should have thrown a runtime exception!";
   CPPUNIT_ASSERT_THROW_MESSAGE(msg3.str(), p.stringValue(1), std::runtime_error);
   */
    f1->removeSection(s.id());
}

void TestProperty::testProperties() {
    Section s = f1->createSection("PropertyTest", "test");
    if (s.hasPropertyByName("TestProperty")) {
        s.removeProperty(s.getPropertyByName("TestProperty").id());
    }
    Property p = s.addProperty("TestProperty");
    p.dataType("string");
    std::string str = "This is a  test string.";
    std::string str2 = "a reference";
    std::string str3 = "a file name";
    p.addValue(str,0.0, str2, str3);

    stringstream msg3;
    msg3
            << "Error changing dataType of not-empty property. Should have thrown a runtime exception!";
    CPPUNIT_ASSERT_THROW_MESSAGE(msg3.str(), p.dataType("double"), std::runtime_error);

    f1->removeSection(s.id());
}
