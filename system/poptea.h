#ifndef POPTEA_H
#define POPTEA_H

    struct PopTea
    {
      struct expEquipment::setup expSetup;
      struct physicalModel::TBCsystem TBCsystem;
//      struct emission model and heat model
//      parameter estimation settings - this means ftol etc
//      parameter estimation algorithms -
//      parameter estimation constraints

      PopTea(struct expEquipment::setup expSetup_,
             struct physicalModel::TBCsystem TBCsystem_);

//    function to make experimental noise should go here
//    function to hold results to should go here too
    };

#endif // POPTEA_H