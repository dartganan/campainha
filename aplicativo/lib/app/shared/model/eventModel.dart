// To parse this JSON data, do
//
//     final eventModel = eventModelFromJson(jsonString);

import 'dart:convert';

EventModel eventModelFromJson(String str) => EventModel.fromJson(json.decode(str));

String eventModelToJson(EventModel data) => json.encode(data.toJson());

class EventModel {
    String uid;
    int timestamp;

    EventModel({
        this.uid,
        this.timestamp,
    });

    factory EventModel.fromJson(Map<String, dynamic> json) => EventModel(
        uid: json["uid"],
        timestamp: json["timestamp"],
    );

    Map<String, dynamic> toJson() => {
        "uid": uid,
        "timestamp": timestamp,
    };
}
