### Dependencies

```mermaid
stateDiagram-v2
    VaccinationsPage --> VaccinationsRange
    OwnersPage --> OwnersRange
    AnimalsPage --> AnimalsRange
    OwnerPage --> OwnerAnimalsRange
    AnimalPage --> TreatmentsRange
```

### Navigation

```mermaid
stateDiagram-v2
    VaccinationsPage --> OwnerPage
    OwnersPage --> OwnerPage
    AnimalsPage --> AnimalPage
    OwnerPage --> AnimalPage
    AnimalPage --> OwnerPage
```