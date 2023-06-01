
// Generated from Dap.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "DapListener.h"


/**
 * This class provides an empty implementation of DapListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  DapBaseListener : public DapListener {
public:

  virtual void enterParse(DapParser::ParseContext * /*ctx*/) override { }
  virtual void exitParse(DapParser::ParseContext * /*ctx*/) override { }

  virtual void enterSas_stmt_list(DapParser::Sas_stmt_listContext * /*ctx*/) override { }
  virtual void exitSas_stmt_list(DapParser::Sas_stmt_listContext * /*ctx*/) override { }

  virtual void enterIf_stmt(DapParser::If_stmtContext * /*ctx*/) override { }
  virtual void exitIf_stmt(DapParser::If_stmtContext * /*ctx*/) override { }

  virtual void enterIf_then_else_stmt(DapParser::If_then_else_stmtContext * /*ctx*/) override { }
  virtual void exitIf_then_else_stmt(DapParser::If_then_else_stmtContext * /*ctx*/) override { }

  virtual void enterDelete_stmt(DapParser::Delete_stmtContext * /*ctx*/) override { }
  virtual void exitDelete_stmt(DapParser::Delete_stmtContext * /*ctx*/) override { }

  virtual void enterDo_stmt(DapParser::Do_stmtContext * /*ctx*/) override { }
  virtual void exitDo_stmt(DapParser::Do_stmtContext * /*ctx*/) override { }

  virtual void enterExpression(DapParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(DapParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterExpressionList(DapParser::ExpressionListContext * /*ctx*/) override { }
  virtual void exitExpressionList(DapParser::ExpressionListContext * /*ctx*/) override { }

  virtual void enterOf_var_list(DapParser::Of_var_listContext * /*ctx*/) override { }
  virtual void exitOf_var_list(DapParser::Of_var_listContext * /*ctx*/) override { }

  virtual void enterIdentifiers_list(DapParser::Identifiers_listContext * /*ctx*/) override { }
  virtual void exitIdentifiers_list(DapParser::Identifiers_listContext * /*ctx*/) override { }

  virtual void enterIn_var_list(DapParser::In_var_listContext * /*ctx*/) override { }
  virtual void exitIn_var_list(DapParser::In_var_listContext * /*ctx*/) override { }

  virtual void enterColonInts(DapParser::ColonIntsContext * /*ctx*/) override { }
  virtual void exitColonInts(DapParser::ColonIntsContext * /*ctx*/) override { }

  virtual void enterLiteral(DapParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(DapParser::LiteralContext * /*ctx*/) override { }

  virtual void enterVariables(DapParser::VariablesContext * /*ctx*/) override { }
  virtual void exitVariables(DapParser::VariablesContext * /*ctx*/) override { }

  virtual void enterAbort_main(DapParser::Abort_mainContext * /*ctx*/) override { }
  virtual void exitAbort_main(DapParser::Abort_mainContext * /*ctx*/) override { }

  virtual void enterAbort_stmt(DapParser::Abort_stmtContext * /*ctx*/) override { }
  virtual void exitAbort_stmt(DapParser::Abort_stmtContext * /*ctx*/) override { }

  virtual void enterFile_spec(DapParser::File_specContext * /*ctx*/) override { }
  virtual void exitFile_spec(DapParser::File_specContext * /*ctx*/) override { }

  virtual void enterProc_main(DapParser::Proc_mainContext * /*ctx*/) override { }
  virtual void exitProc_main(DapParser::Proc_mainContext * /*ctx*/) override { }

  virtual void enterProc_stmt(DapParser::Proc_stmtContext * /*ctx*/) override { }
  virtual void exitProc_stmt(DapParser::Proc_stmtContext * /*ctx*/) override { }

  virtual void enterProc_name(DapParser::Proc_nameContext * /*ctx*/) override { }
  virtual void exitProc_name(DapParser::Proc_nameContext * /*ctx*/) override { }

  virtual void enterArray_main(DapParser::Array_mainContext * /*ctx*/) override { }
  virtual void exitArray_main(DapParser::Array_mainContext * /*ctx*/) override { }

  virtual void enterArray_stmt(DapParser::Array_stmtContext * /*ctx*/) override { }
  virtual void exitArray_stmt(DapParser::Array_stmtContext * /*ctx*/) override { }

  virtual void enterArray_name(DapParser::Array_nameContext * /*ctx*/) override { }
  virtual void exitArray_name(DapParser::Array_nameContext * /*ctx*/) override { }

  virtual void enterArray_subscript(DapParser::Array_subscriptContext * /*ctx*/) override { }
  virtual void exitArray_subscript(DapParser::Array_subscriptContext * /*ctx*/) override { }

  virtual void enterArray_elements(DapParser::Array_elementsContext * /*ctx*/) override { }
  virtual void exitArray_elements(DapParser::Array_elementsContext * /*ctx*/) override { }

  virtual void enterInitial_value_list(DapParser::Initial_value_listContext * /*ctx*/) override { }
  virtual void exitInitial_value_list(DapParser::Initial_value_listContext * /*ctx*/) override { }

  virtual void enterInitial_value_list_item(DapParser::Initial_value_list_itemContext * /*ctx*/) override { }
  virtual void exitInitial_value_list_item(DapParser::Initial_value_list_itemContext * /*ctx*/) override { }

  virtual void enterInitial_value_list_bk(DapParser::Initial_value_list_bkContext * /*ctx*/) override { }
  virtual void exitInitial_value_list_bk(DapParser::Initial_value_list_bkContext * /*ctx*/) override { }

  virtual void enterConstant_iter_value(DapParser::Constant_iter_valueContext * /*ctx*/) override { }
  virtual void exitConstant_iter_value(DapParser::Constant_iter_valueContext * /*ctx*/) override { }

  virtual void enterConstant_value(DapParser::Constant_valueContext * /*ctx*/) override { }
  virtual void exitConstant_value(DapParser::Constant_valueContext * /*ctx*/) override { }

  virtual void enterAssign_main(DapParser::Assign_mainContext * /*ctx*/) override { }
  virtual void exitAssign_main(DapParser::Assign_mainContext * /*ctx*/) override { }

  virtual void enterAssign_stmt(DapParser::Assign_stmtContext * /*ctx*/) override { }
  virtual void exitAssign_stmt(DapParser::Assign_stmtContext * /*ctx*/) override { }

  virtual void enterBy_main(DapParser::By_mainContext * /*ctx*/) override { }
  virtual void exitBy_main(DapParser::By_mainContext * /*ctx*/) override { }

  virtual void enterBy_stmt(DapParser::By_stmtContext * /*ctx*/) override { }
  virtual void exitBy_stmt(DapParser::By_stmtContext * /*ctx*/) override { }

  virtual void enterCall_main(DapParser::Call_mainContext * /*ctx*/) override { }
  virtual void exitCall_main(DapParser::Call_mainContext * /*ctx*/) override { }

  virtual void enterCall_stmt(DapParser::Call_stmtContext * /*ctx*/) override { }
  virtual void exitCall_stmt(DapParser::Call_stmtContext * /*ctx*/) override { }

  virtual void enterData_main(DapParser::Data_mainContext * /*ctx*/) override { }
  virtual void exitData_main(DapParser::Data_mainContext * /*ctx*/) override { }

  virtual void enterData_stmt(DapParser::Data_stmtContext * /*ctx*/) override { }
  virtual void exitData_stmt(DapParser::Data_stmtContext * /*ctx*/) override { }

  virtual void enterDataset_name_opt(DapParser::Dataset_name_optContext * /*ctx*/) override { }
  virtual void exitDataset_name_opt(DapParser::Dataset_name_optContext * /*ctx*/) override { }

  virtual void enterDatastmt_cmd(DapParser::Datastmt_cmdContext * /*ctx*/) override { }
  virtual void exitDatastmt_cmd(DapParser::Datastmt_cmdContext * /*ctx*/) override { }

  virtual void enterView_dsname_opt(DapParser::View_dsname_optContext * /*ctx*/) override { }
  virtual void exitView_dsname_opt(DapParser::View_dsname_optContext * /*ctx*/) override { }

  virtual void enterView_name(DapParser::View_nameContext * /*ctx*/) override { }
  virtual void exitView_name(DapParser::View_nameContext * /*ctx*/) override { }

  virtual void enterDataset_name(DapParser::Dataset_nameContext * /*ctx*/) override { }
  virtual void exitDataset_name(DapParser::Dataset_nameContext * /*ctx*/) override { }

  virtual void enterProgram_name(DapParser::Program_nameContext * /*ctx*/) override { }
  virtual void exitProgram_name(DapParser::Program_nameContext * /*ctx*/) override { }

  virtual void enterPasswd_opt(DapParser::Passwd_optContext * /*ctx*/) override { }
  virtual void exitPasswd_opt(DapParser::Passwd_optContext * /*ctx*/) override { }

  virtual void enterSource_opt(DapParser::Source_optContext * /*ctx*/) override { }
  virtual void exitSource_opt(DapParser::Source_optContext * /*ctx*/) override { }

  virtual void enterDatalines_main(DapParser::Datalines_mainContext * /*ctx*/) override { }
  virtual void exitDatalines_main(DapParser::Datalines_mainContext * /*ctx*/) override { }

  virtual void enterDatalines_stmt(DapParser::Datalines_stmtContext * /*ctx*/) override { }
  virtual void exitDatalines_stmt(DapParser::Datalines_stmtContext * /*ctx*/) override { }

  virtual void enterDatalines4_stmt(DapParser::Datalines4_stmtContext * /*ctx*/) override { }
  virtual void exitDatalines4_stmt(DapParser::Datalines4_stmtContext * /*ctx*/) override { }

  virtual void enterDrop_main(DapParser::Drop_mainContext * /*ctx*/) override { }
  virtual void exitDrop_main(DapParser::Drop_mainContext * /*ctx*/) override { }

  virtual void enterDrop_stmt(DapParser::Drop_stmtContext * /*ctx*/) override { }
  virtual void exitDrop_stmt(DapParser::Drop_stmtContext * /*ctx*/) override { }

  virtual void enterInfile_main(DapParser::Infile_mainContext * /*ctx*/) override { }
  virtual void exitInfile_main(DapParser::Infile_mainContext * /*ctx*/) override { }

  virtual void enterInfile_stmt(DapParser::Infile_stmtContext * /*ctx*/) override { }
  virtual void exitInfile_stmt(DapParser::Infile_stmtContext * /*ctx*/) override { }

  virtual void enterFile_specification(DapParser::File_specificationContext * /*ctx*/) override { }
  virtual void exitFile_specification(DapParser::File_specificationContext * /*ctx*/) override { }

  virtual void enterDevice_type(DapParser::Device_typeContext * /*ctx*/) override { }
  virtual void exitDevice_type(DapParser::Device_typeContext * /*ctx*/) override { }

  virtual void enterInfile_options(DapParser::Infile_optionsContext * /*ctx*/) override { }
  virtual void exitInfile_options(DapParser::Infile_optionsContext * /*ctx*/) override { }

  virtual void enterInput_main(DapParser::Input_mainContext * /*ctx*/) override { }
  virtual void exitInput_main(DapParser::Input_mainContext * /*ctx*/) override { }

  virtual void enterInput_stmt(DapParser::Input_stmtContext * /*ctx*/) override { }
  virtual void exitInput_stmt(DapParser::Input_stmtContext * /*ctx*/) override { }

  virtual void enterPut_stmt(DapParser::Put_stmtContext * /*ctx*/) override { }
  virtual void exitPut_stmt(DapParser::Put_stmtContext * /*ctx*/) override { }

  virtual void enterInput_specification(DapParser::Input_specificationContext * /*ctx*/) override { }
  virtual void exitInput_specification(DapParser::Input_specificationContext * /*ctx*/) override { }

  virtual void enterPut_specification(DapParser::Put_specificationContext * /*ctx*/) override { }
  virtual void exitPut_specification(DapParser::Put_specificationContext * /*ctx*/) override { }

  virtual void enterPointer_control(DapParser::Pointer_controlContext * /*ctx*/) override { }
  virtual void exitPointer_control(DapParser::Pointer_controlContext * /*ctx*/) override { }

  virtual void enterInformat_list(DapParser::Informat_listContext * /*ctx*/) override { }
  virtual void exitInformat_list(DapParser::Informat_listContext * /*ctx*/) override { }

  virtual void enterInput_variable_format(DapParser::Input_variable_formatContext * /*ctx*/) override { }
  virtual void exitInput_variable_format(DapParser::Input_variable_formatContext * /*ctx*/) override { }

  virtual void enterInput_variable(DapParser::Input_variableContext * /*ctx*/) override { }
  virtual void exitInput_variable(DapParser::Input_variableContext * /*ctx*/) override { }

  virtual void enterPut_variable_format(DapParser::Put_variable_formatContext * /*ctx*/) override { }
  virtual void exitPut_variable_format(DapParser::Put_variable_formatContext * /*ctx*/) override { }

  virtual void enterPut_variable(DapParser::Put_variableContext * /*ctx*/) override { }
  virtual void exitPut_variable(DapParser::Put_variableContext * /*ctx*/) override { }

  virtual void enterColumn_point_control(DapParser::Column_point_controlContext * /*ctx*/) override { }
  virtual void exitColumn_point_control(DapParser::Column_point_controlContext * /*ctx*/) override { }

  virtual void enterLine_point_control(DapParser::Line_point_controlContext * /*ctx*/) override { }
  virtual void exitLine_point_control(DapParser::Line_point_controlContext * /*ctx*/) override { }

  virtual void enterFormat_modifier(DapParser::Format_modifierContext * /*ctx*/) override { }
  virtual void exitFormat_modifier(DapParser::Format_modifierContext * /*ctx*/) override { }

  virtual void enterColumn_specifications(DapParser::Column_specificationsContext * /*ctx*/) override { }
  virtual void exitColumn_specifications(DapParser::Column_specificationsContext * /*ctx*/) override { }

  virtual void enterMeans_main(DapParser::Means_mainContext * /*ctx*/) override { }
  virtual void exitMeans_main(DapParser::Means_mainContext * /*ctx*/) override { }

  virtual void enterMeans_proc(DapParser::Means_procContext * /*ctx*/) override { }
  virtual void exitMeans_proc(DapParser::Means_procContext * /*ctx*/) override { }

  virtual void enterRun_main(DapParser::Run_mainContext * /*ctx*/) override { }
  virtual void exitRun_main(DapParser::Run_mainContext * /*ctx*/) override { }

  virtual void enterRun_stmt(DapParser::Run_stmtContext * /*ctx*/) override { }
  virtual void exitRun_stmt(DapParser::Run_stmtContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

