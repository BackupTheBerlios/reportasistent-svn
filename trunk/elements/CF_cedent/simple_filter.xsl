<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          
	
	<xsl:template match="/active_list">		
		<xsl:text disable-output-escaping="yes">

&lt;dialog_data&gt;
	</xsl:text>				

		<xsl:apply-templates select="node()[position()=1]" mode="attributes"/>





		<xsl:text disable-output-escaping="yes">
	&lt;values&gt;</xsl:text>				
	

		<xsl:apply-templates select="node()" mode="values"/>

		<xsl:text disable-output-escaping="yes">
	&lt;/values&gt;
		</xsl:text>				




		<xsl:text disable-output-escaping="yes">
&lt;/dialog_data&gt;
		</xsl:text>				
	</xsl:template>

	
	



	<!-- vypise atributy -->
	<xsl:template match="node()" mode="attributes">		

	<attributes>
		

		<xsl:apply-templates select="@*" mode="attributes"/>

<!--

<xsl:text disable-output-escaping="yes">
		</xsl:text>
		<attribute name="missing_values"/>
		-->
<xsl:text disable-output-escaping="yes">
		</xsl:text>
		<attribute name="structure"/>



<xsl:text disable-output-escaping="yes">
	</xsl:text>				
	</attributes>


	</xsl:template>
	


	<!-- vypise vsechny atributy -->
	<xsl:template match="@*" mode="attributes">
	
		<xsl:text disable-output-escaping="yes">
		&lt;attribute name="</xsl:text>
	
		<xsl:value-of select="name()"/>
	
		<!-- =<xsl:value-of select="."/> -->

		<xsl:text disable-output-escaping="yes">"/&gt;</xsl:text>

	</xsl:template>






	<!-- vypise hodnoty -->
	<xsl:template match="node()" mode="values">		
		

		<xsl:text disable-output-escaping="yes">
		&lt;value </xsl:text>
		<xsl:apply-templates select="@*" mode="values"/>

		<xsl:text disable-output-escaping="yes">structure="</xsl:text>
		<xsl:apply-templates select="sub_CF_cedent" mode="values"/>
		<xsl:text disable-output-escaping="yes">" </xsl:text>
		<!--
		<xsl:text disable-output-escaping="yes">missing_values="</xsl:text>
		<xsl:apply-templates select="missing_value" mode="values"/>
		<xsl:text disable-output-escaping="yes">"</xsl:text>
        -->
		<xsl:text disable-output-escaping="yes">/&gt;</xsl:text>


	</xsl:template>



	<!-- naplni hodnotu pro categories -->
	<xsl:template match="sub_CF_cedent" mode="values">
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no">; </xsl:text>
		</xsl:if>

		<xsl:text disable-output-escaping="no">(name: </xsl:text>
		<xsl:value-of select="@name"/>
		<xsl:text disable-output-escaping="no">; literal_cnt: </xsl:text>
		<xsl:value-of select="@literal_cnt"/>
		<xsl:text disable-output-escaping="no">; length: </xsl:text>
		<xsl:value-of select="@length"/>
		<xsl:text disable-output-escaping="no">; literals: {</xsl:text>
		
		<xsl:apply-templates select="CF_literal" mode="values"/>
		<xsl:text disable-output-escaping="no">}</xsl:text>
		<xsl:text disable-output-escaping="no">)</xsl:text>
	</xsl:template>



	
	<xsl:template match="CF_literal" mode="values">
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no">; </xsl:text>
		</xsl:if>
		
		<xsl:text disable-output-escaping="no">(underlying attribute: </xsl:text>
		<xsl:value-of select="@underlying_attribute"/>
		<xsl:text disable-output-escaping="no">; category_cnt: </xsl:text>
		<xsl:value-of select="@category_cnt"/>
		<xsl:text disable-output-escaping="no">)</xsl:text>
	</xsl:template>



	<!-- naplni hodnotu -->
	<xsl:template match="@*" mode="values">
	
		<xsl:value-of select="name()"/>
		
		<xsl:text disable-output-escaping="yes">="</xsl:text>
	
		<xsl:value-of select="."/>

		<xsl:text disable-output-escaping="yes">" </xsl:text>

	</xsl:template>

	



</xsl:stylesheet>
