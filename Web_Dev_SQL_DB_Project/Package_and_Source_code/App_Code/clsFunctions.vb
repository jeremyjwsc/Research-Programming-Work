
Imports System.Data.SqlClient
Public Class clsFunctions
    Inherits System.Web.UI.Page
    Dim dbConnectStr As String = Nothing
    Dim HostServer As String = ""
    Dim dbFileName As String = ""
    Dim HostUserId As String = ""
    Dim HostPassword As String = ""
    Dim IsIntegratedSecurity As Boolean = False
    Dim ServerPath As String = Server.MapPath("~/")

    Public Sub New()
        Settings()
        dbConnectStr =
                        "Server=" & HostServer &
                        ";Database=" & dbFileName &
                        ";User ID=" & HostUserId &
                        ";Password=" & HostPassword
        If IsIntegratedSecurity = True Then dbConnectStr = dbConnectStr & ";Integrated Security=True"
        dbConnectStr = dbConnectStr & ";Asynchronous Processing=True;MultipleActiveResultSets=True"
    End Sub

    Private Sub Settings()
        Dim txtStr As String = My.Computer.FileSystem.ReadAllText(ServerPath & "Settings.txt")
        Dim Settings() As String = Split(txtStr, "|")
        HostServer = Settings(0)
        dbFileName = Settings(1)
        HostUserId = Settings(2)
        HostPassword = Settings(3)
        IsIntegratedSecurity = Settings(4)
    End Sub
    Public Function SqlTransact(ByVal sqlStr As String, Optional ByRef errDes As String = "",
                                Optional ByRef EffectedRows As Integer = 0) As Boolean
        SqlTransact = False
        Try
            Dim cnSql As New SqlConnection
            cnSql.ConnectionString = dbConnectStr
            cnSql.Open()
            Dim cmdSql As SqlCommand = New SqlCommand(sqlStr, cnSql)
            EffectedRows = cmdSql.ExecuteNonQuery
            cnSql.Close()
            SqlTransact = True
        Catch ex As Exception
            errDes = ex.Message & " - [SqlTransact]"
        End Try
    End Function
    Public Function SqlDataRead(ByVal sqlStr As String, ByRef errDes As String) As SqlDataReader
        SqlDataRead = Nothing
        Try
            Dim cnSql As New SqlConnection
            cnSql.ConnectionString = dbConnectStr
            cnSql.Open()
            Dim cmdSql As SqlCommand = New SqlCommand(sqlStr, cnSql)
            SqlDataRead = cmdSql.ExecuteReader
        Catch ex As Exception
            errDes = ex.Message & " - [SqlDataRead]"
        End Try
    End Function



End Class
