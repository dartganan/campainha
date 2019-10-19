import 'package:flutter/material.dart';
import 'package:darthome/app/pages/home/home_module.dart';
import 'package:firebase_messaging/firebase_messaging.dart';

class AppWidget extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    final FirebaseMessaging _firebaseMessaging = FirebaseMessaging();

    _firebaseMessaging.subscribeToTopic("campainha");

    _firebaseMessaging.configure(
      onMessage: (Map<String, dynamic> message) async {
        print("onMessage: $message");
      },
      //onBackgroundMessage: myBackgroundMessageHandler,
      onLaunch: (Map<String, dynamic> message) async {
        print("onLaunch: $message");
      },
      onResume: (Map<String, dynamic> message) async {
        print("onResume: $message");
      },
    );

    print("_firebaseMessaging.getToken();");
    print(_firebaseMessaging.getToken().then((val) {
      print(val);
    }));

    return MaterialApp(
      title: 'Campainha',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: HomeModule(),
    );
  }
}
