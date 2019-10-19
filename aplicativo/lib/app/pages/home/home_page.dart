import 'package:darthome/app/pages/home/home_bloc.dart';
import 'package:darthome/app/pages/home/home_module.dart';
import 'package:darthome/app/shared/model/eventModel.dart';
import 'package:flutter/material.dart';
import 'package:timeline/model/timeline_model.dart';
import 'package:timeline/timeline.dart';

class HomePage extends StatefulWidget {
  @override
  _HomePageState createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {

  final homeBloc = HomeModule.to.getBloc<HomeBloc>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        backgroundColor: Colors.white,
        appBar: AppBar(
          title: Text("Campainha Wi-Fi"),
        ),
        body: Column(
          children: <Widget>[
            SizedBox(
              height: 20,
            ),
            Text(
              "Histórico de chamadas",
              style: TextStyle(fontSize: 20),
            ),
            SizedBox(
              height: 20,
            ),
            Expanded(
              child: StreamBuilder<List<EventModel>>(
                stream: homeBloc.historyStream,
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
                   return TimelineComponent(
                      timelineList: snapshot.data.map((event) => TimelineModel(title: formatDate(DateTime.fromMillisecondsSinceEpoch(event.timestamp)), description: "Camapinha tocou" )).toList());
                  }
                  return Center(child: CircularProgressIndicator(),);
                },
              ), 
            )
          ],
        ));
  }

  formatDate(DateTime date) {
    return "${date.day.toString().padLeft(2, '0')}/${date.month.toString().padLeft(2, '0')}/${date.year} às ${date.hour.toString().padLeft(2, '0')}:${date.minute.toString().padLeft(2, '0')}:${date.second.toString().padLeft(2, '0')}";
  }

}
