/*

옵저버 패턴

이벤트를 보내는쪽과 받는쪽을 분리하여 이벤트를 관리한다.
Player는 Subject를 만들고   구독Object에서는 Subject에 Observer를 파견(?)보내고 상태변화를 관찰한다

즉 옵저버 패턴은 오브젝트의 상태변화를 관찰하는 패턴이다.
*/


/*
옵저버 패턴의 구조


        class Subject(관찰 대상)                          ----------->           class Observer
        list<Observer*> lst;
            -Subscribe(Observer * p )   구독
            -UnSubScribe(Oberver * p)   언팔





    


*/