Imports System.Data.SqlClient
Partial Class Average
    Inherits System.Web.UI.Page
    Dim fn As New clsFunctions
    Dim errDes As String = ""
    Private Sub frmMain_Load(sender As Object, e As EventArgs) Handles frmMain.Load
        lbStatus.Text = ""
        lbToRec.Text = "0"
        lbAvgSalary.Text = "0.00"
        Average()
    End Sub
    Private Sub Average()
        Dim MaxDateTime As DateTime = Nothing
        Dim MinDateTime As DateTime = Nothing
        Dim ToRec As UInteger = 0
        Dim ToSalary As Double = 0
        Dim sqlStr As String =
            " SELECT MAX(Timestamp) AS MaxDateTime, MIN(Timestamp) AS MinDateTime," &
            " COUNT(ID) AS ToRec, SUM(Salary) AS ToSalary FROM [dbo].[Records]"
        Dim Reader As SqlDataReader = fn.SqlDataRead(sqlStr, errDes)
        If Reader Is Nothing Then
            lbStatus.Text = errDes
        Else
            If Reader.HasRows = False Then Exit Sub
            If Reader.Read() = True Then
                If IsDBNull(Reader("MaxDateTime")) = False Then MaxDateTime = Reader("MaxDateTime")
                If IsDBNull(Reader("MinDateTime")) = False Then MinDateTime = Reader("MinDateTime")
                If IsDBNull(Reader("ToRec")) = False Then ToRec = Reader("ToRec")
                If IsDBNull(Reader("ToSalary")) = False Then ToSalary = Reader("ToSalary")
            End If
        End If


        lbToRec.Text = ToRec
        lbAvgSalary.Text = Format(Fix(ToSalary / ToRec), "0.00")
        lbTimestamp.Text = MaxDateTime
    End Sub

End Class
