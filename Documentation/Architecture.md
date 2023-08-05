# Overview
We are using the Model View ViewModel architecture for this application.

Model      -> DataAggregator
View       -> View classes + LVGL
View Model -> ViewModel classes

# Updating the view
We have implemented SwiftUI's @ObservedObject pattern in the form of a ObservedObject class. When an ObservedObject instance is updated using its setter, it publishes the change to all of its listeners. This eliminates the need to poll the model for changes.