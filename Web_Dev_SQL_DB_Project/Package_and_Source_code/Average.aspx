<%@ Page Language="VB" AutoEventWireup="false" CodeFile="Average.aspx.vb" Inherits="Average" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
        <style>
        .lnkBtn{
            margin:5px 5px 5px 5px;
            display:inline;
       
        }
    </style>
</head>
<body>
        <div style="width:700px;margin:auto;text-align:left;border-radius:10px;border-width:2px;border-style:solid;
         border-color:rgb(175,175,255);background-color:rgb(215,215,255);font-family:sans-serif;">
        <form id="frmMain" runat="server" style="padding:10px 10px 10px 10px">
            <asp:ScriptManager ID="sm" runat="server"></asp:ScriptManager>
            <asp:UpdateProgress ID="upMain" runat="server">
                <ProgressTemplate>
                    <p>Processing...</p>
                </ProgressTemplate>
            </asp:UpdateProgress>
            <asp:UpdatePanel ID="updName" runat="server">
                <ContentTemplate>
                    <div style="text-align:right;">
                        <asp:Label ID="lbStatus" runat="server" ForeColor="Red" Text="#Status#"></asp:Label>
                    </div>
                   <div style="text-align:right;">
                       <asp:HyperLink ID="hpLnkHome" runat="server" CssClass="lnkBtn" NavigateUrl="~/Default.aspx">Home</asp:HyperLink>
                       <asp:HyperLink ID= "hpLnkRecords" runat="server" CssClass="lnkBtn" NavigateUrl="~/Records.aspx">Records</asp:HyperLink>
                    </div>
                    <div style="text-align:center; margin-top:10px;background-color: rgb(200,200,200);">
                        <p style="background-color: rgb(192,192,192);padding:3px 3px 3px 3px; font-weight:bold;">Average</p>
                        <table style="width:600px;margin:auto;">
                            <tr style="font-weight:bold;">
                                <td>Total Record</td><td>Salary</td><td>Timestamp</td>
                            </tr>
                            <tr>
                                <td><asp:Label ID="lbToRec" runat="server" Text="#ToRec#" Font-Size="Small" Width="200"></asp:Label></td>
                                <td><asp:Label ID="lbAvgSalary" runat="server" Text="#AvgSalary#" Font-Size="Small" Width="200"></asp:Label></td>
                                <td><asp:Label ID="lbTimestamp" runat="server" Text="#Timestamp#" Font-Size="Small" Width="200"></asp:Label></td>
                            </tr>
                        </table>
                    </div>
                </ContentTemplate>
            
            </asp:UpdatePanel>
       </form>
    </div>
</body>
</html>
