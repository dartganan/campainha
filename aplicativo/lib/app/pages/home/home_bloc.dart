import 'package:bloc_pattern/bloc_pattern.dart';
import 'package:darthome/app/shared/model/eventModel.dart';
import 'package:firebase_database/firebase_database.dart';

class HomeBloc extends BlocBase {
  final FirebaseDatabase database = new FirebaseDatabase();

  Stream<List<EventModel>> historyStream;

  HomeBloc() {

    historyStream = FirebaseDatabase.instance
        .reference()
        .child("campainha")
        .child("principal")
        .onValue
        .map((event) => transFormEvent(event.snapshot.value));
  }
  @override
  void dispose() {
    super.dispose();
  }
}

List<EventModel> transFormEvent(Map<dynamic, dynamic> listEvents) {
  final listEventModel = <EventModel>[];
  listEvents.forEach((key, val) {
    EventModel event = EventModel.fromJson({"uid": key, "timestamp": val});
    listEventModel.add(event);
  });
  // ordena por data
  listEventModel.sort((a, b) => b.timestamp.compareTo(a.timestamp));
  return listEventModel;
}
