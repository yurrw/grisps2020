<html>
    <head>
    <title>nnap</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <style>
        .title{
            font-family: "Comic Sans MS", "Comic Sans", cursive;
        }
    </style>
    </head>
    <body>
    <nav class="navbar navbar-expand-sm bg-light">

    <ul class="navbar-nav">
    <img src="https://imgur.com/S0fFaAn.png" width=50 heigth=40 ></img>
    <h1  class="title">&nbsp NNAP </h1>
    </ul>

    </nav>
    <br>
    <div class="row">
        <div class="col-md-12">
            <p > &nbsp&nbsp Faça abaixo sua varredura: </p>
        </div>
    </div>
    <hr>
        <form action="/startScan" method="get">
            &nbsp&nbsp IP/nome: <input type="text" name="url" required>
            &nbsp&nbsp  Porta de início: <input type="number" name="startPort"  min="0" required>
            &nbsp&nbsp Porta Final: <input type="number" name="endPort"  min="0" required>
            <br>
            <br>
            <p  class="font-weight-bold" >&nbsp&nbsp care, next field might be harmful   </p>
            &nbsp&nbsp Threads: <input type="number" name="threadsAtTime"  min="2" required  value=2>
            <input type="submit" value="Varrer,go!">
        </form>

        &nbsp&nbsp *obs: Porta final não pode ser menor ou igual a porta inicial.
        <br>
        &nbsp&nbsp *obs: O número de threads deve ser algum múltiplo valido da quantidade de portas (PortaFinal - PortaInicial).
        <br>
        &nbsp&nbsp *obs: O tempo de resposta do servidor do ip/nome pode afetar o desempenho da ferramenta.
        <br>

        &nbsp&nbsp *obs: Spawnar muitas threads pode ocasionar em bloqueio do seu ip no remetente.
            <br>
            <br>

        <table class="table">
        <thead>
            <tr>
            <th scope="col">#</th>
            <th scope="col">Porta</th>
            <th scope="col">Provavel serviço</th>
            </tr>
        </thead>
        <tbody>
            {{ range $i,$item := .Ps}}
            <tr>
                <th scope="row">#</th>
                <td>{{$i}}</td>
                <td>{{$item}} </td>
            </tr> 
            {{ end }}
        
        </tbody>
        </table>
    </body>
</html>
