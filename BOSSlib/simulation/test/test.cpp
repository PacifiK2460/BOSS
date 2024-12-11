#define CATCH_CONFIG_MAIN
#include "catch2/catch.h"

#include <nanoid/nanoid.h>
#include <simulation.h>
#include <generic_resource.h>
#include <generic_process.h>

TEST_CASE("TestBasicProcessCreation") {
    Process::Process process = Process::Process("TestProcess", Process::ProcessResourceIntensity::LOW);
    REQUIRE(process.getName() == "TestProcess");
    REQUIRE(process.getIntensity() == Process::ProcessResourceIntensity::LOW);
    REQUIRE(process.getResources()->size() == 0);
}

TEST_CASE("TestBasicResourceCreation") {
    Resource::Resource resource = Resource::Resource("TestResource", 1000);
    REQUIRE(resource.getName() == "TestResource");
    REQUIRE(resource.getTotalAmount() == 1000);
}

TEST_CASE("TestBasicProcessResourceManagement") {
    Process::Process process = Process::Process("TestProcess", Process::ProcessResourceIntensity::LOW);
    Resource::Resource resource = Resource::Resource("TestResource", 1000);

    process.addResource(&resource, 100);
    REQUIRE(process.getResources()->size() == 1);
    REQUIRE(process.getResources()->at(0).getResource() == &resource);
    REQUIRE(process.getResources()->at(0).getAmount() == 100);

    process.removeResource(resource.getId());
    REQUIRE(process.getResources()->size() == 0);
}

TEST_CASE("TestSimulationCreation") {
    Simulation::Simulation simulation = Simulation::Simulation(60);
    REQUIRE(simulation.getProcesses()->size() == 0);
    REQUIRE(simulation.getResources()->size() == 0);
}

TEST_CASE("TestSimulationProcessManagement") {
    Simulation::Simulation simulation = Simulation::Simulation(60);
    Process::Process process = Process::Process("TestProcess", Process::ProcessResourceIntensity::LOW);

    simulation.addProcess(process);
    REQUIRE(simulation.getProcesses()->size() == 1);
    REQUIRE(simulation.getProcesses()->at(0)->getName() == "TestProcess");

    simulation.removeProcess(process.getId());
    REQUIRE(simulation.getProcesses()->size() == 0);
}

TEST_CASE("TestProcessResourcePreparationWithNoIntensity") {
    Process::Process process = Process::Process("TestProcess", Process::ProcessResourceIntensity::NONE);
    Resource::Resource resource1 = Resource::Resource("TestResource", 1000);
    Resource::Resource resource2 = Resource::Resource("TestResource2", 1500);

    process.addResource(&resource1, 100);
    process.addResource(&resource2, 100);

    Simulation::Simulation simulation = Simulation::Simulation();
    simulation.addProcess(process);
    simulation.addResource(resource1);
    simulation.addResource(resource2);

    simulation.start();

    REQUIRE(resource1.getFreeAmount() == 900);
    REQUIRE(resource2.getFreeAmount() == 1400);
}

TEST_CASE("TestProcessResourcePreparationWithLowIntensity") {
    Process::Process process = Process::Process("TestProcess", Process::ProcessResourceIntensity::LOW);
    Resource::Resource resource1 = Resource::Resource("TestResource", 1000);
    Resource::Resource resource2 = Resource::Resource("TestResource2", 1500);

    process.addResource(&resource1, 100);
    process.addResource(&resource2, 100);

    Simulation::Simulation simulation = Simulation::Simulation();
    simulation.addProcess(process);
    simulation.addResource(resource1);
    simulation.addResource(resource2);

    simulation.start();

    REQUIRE(resource1.getFreeAmount() <= 900);
    REQUIRE(resource2.getFreeAmount() <= 1400);
}

TEST_CASE("TestSimulationProcessInformationEdit") {
    Simulation::Simulation simulation = Simulation::Simulation();
    Process::Process process = Process::Process("TestProcess", Process::ProcessResourceIntensity::LOW);
    simulation.addProcess(process);

    // Get process by id, edit it and check if it was edited
    auto processPtr = simulation.getProcesses()->at(0);
    auto processId = processPtr->getId();

    processPtr->setName("EditedName");

    REQUIRE(simulation.getProcess(processId)->getName() == "EditedName");
}

TEST_CASE("GENERIC") {
    Simulation::Simulation simulation(60);
    REQUIRE(simulation.getProcesses()->size() == 0);
    REQUIRE(simulation.getResources()->size() == 0);

    Process::Process process = Process::Process("TestProcess", Process::ProcessResourceIntensity::LOW);
    Resource::Resource resource = Resource::Resource("TestResource", 1000);

    simulation.addProcess(process);
    simulation.addResource(resource);

    REQUIRE(simulation.getProcesses()->size() == 1);
    REQUIRE(simulation.getResources()->size() == 1);

    simulation.removeProcess(process.getId());
    simulation.removeResource(resource.getId());

    REQUIRE(simulation.getProcesses()->size() == 0);
    REQUIRE(simulation.getResources()->size() == 0);


}