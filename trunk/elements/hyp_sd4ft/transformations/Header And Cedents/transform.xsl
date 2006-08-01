<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
      
	
<!-- nastaveni jazyka (defaultne cestina)-->
<xsl:variable name="lng">cz</xsl:variable>


<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="Header"></xsl:variable>
<xsl:variable name="ShowAntecedent">true</xsl:variable>
<xsl:variable name="ShowSuccedent">true</xsl:variable>
<xsl:variable name="ShowCondition">true</xsl:variable>      
<xsl:variable name="ShowFirstSet">true</xsl:variable>      
<xsl:variable name="ShowSecondSet">true</xsl:variable>      
	
	
	


<xsl:template match="hyp_sd4ft"> <!-- nezpomen prepsat na match="/hyp_4ft" - odebrat lomitko -->

		
	<chapter title="{$Header}">

	<xsl:if test="$ShowAntecedent='true'">	
		<xsl:apply-templates select="id(@antecedent)"/>
	</xsl:if>
	
	<xsl:if test="$ShowSuccedent='true'">	
		<xsl:apply-templates select="id(@succedent)"/>
	</xsl:if>
	
	<xsl:if test="$ShowCondition='true'">		
		<xsl:apply-templates select="id(@condition)"/>
	</xsl:if>
	
	<xsl:if test="$ShowFirstSet='true'">		
		<xsl:apply-templates select="id(@set1)"/>
	</xsl:if>
	
	<xsl:if test="$ShowSecondSet='true'">		
		<xsl:apply-templates select="id(@set2)"/>
	</xsl:if>
	
	</chapter>
	

</xsl:template>
	



	


	<xsl:template match="ti_cedent">
	
	<paragraph>
		
		<text>
			<xsl:value-of select="@type"/>:<br/>			
			<xsl:apply-templates select="ti_literal"/>
			<br/>
		</text>
		
	</paragraph>
		
	</xsl:template>
	
	



	<xsl:template match="ti_literal">
		<xsl:if test="position()!=1">
			<br/>
		</xsl:if>

		<xsl:value-of select="@quant"/>:<tab/><xsl:value-of select="@value"/>
						
	
	</xsl:template>
      




</xsl:stylesheet>
