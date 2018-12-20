/*
 * Copyright (C) 2018 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <gtest/gtest.h>

#include <ignition/common/Console.hh>
#include <ignition/gazebo/components/Joint.hh>
#include <ignition/gazebo/components/Link.hh>
#include <ignition/gazebo/components/Model.hh>
#include <ignition/gazebo/components/Name.hh>
#include <ignition/gazebo/components/ParentEntity.hh>
#include <ignition/gazebo/EntityComponentManager.hh>
#include <ignition/gazebo/Model.hh>

using namespace ignition::gazebo;

class ModelIntegrationTest : public ::testing::TestWithParam<int>
{
  public: void SetUp()
  {
    ignition::common::Console::SetVerbosity(4);
  }
};

//////////////////////////////////////////////////
TEST(ModelIntegrationTest, LinkByName)
{
  EntityComponentManager ecm;

  // Model
  auto eModel = ecm.CreateEntity();
  Model model(eModel);
  EXPECT_EQ(eModel, model.Id());

  // Link
  auto eLink = ecm.CreateEntity();
  ecm.CreateComponent<components::Link>(eLink, components::Link());
  ecm.CreateComponent<components::ParentEntity>(eLink,
      components::ParentEntity(eModel));
  ecm.CreateComponent<components::Name>(eLink,
      components::Name("link_name"));

  // Check model
  EXPECT_EQ(eLink, model.LinkByName(ecm, "link_name"));
}

//////////////////////////////////////////////////
TEST(ModelIntegrationTest, JointByName)
{
  EntityComponentManager ecm;

  // Model
  auto eModel = ecm.CreateEntity();
  Model model(eModel);
  EXPECT_EQ(eModel, model.Id());

  // Joint
  auto eJoint = ecm.CreateEntity();
  ecm.CreateComponent<components::Joint>(eJoint, components::Joint());
  ecm.CreateComponent<components::ParentEntity>(eJoint,
      components::ParentEntity(eModel));
  ecm.CreateComponent<components::Name>(eJoint,
      components::Name("joint_name"));

  // Check model
  EXPECT_EQ(eJoint, model.JointByName(ecm, "joint_name"));
}
