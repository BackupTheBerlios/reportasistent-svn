<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">

 
 
 <!-- nastaveni jazyka (defaultne cestina)-->
	<xsl:variable name="lng">cz</xsl:variable>     
	

	
	<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="FirstSetShow">true</xsl:variable>
<xsl:variable name="SecondSetShow">true</xsl:variable>
<xsl:variable name="GraphType">xl3DColumn</xsl:variable>
<xsl:variable name="ValuesType">abs</xsl:variable>
<xsl:variable name="GraphTitle">SD-CF Graph</xsl:variable>
<xsl:variable name="LegendShow">true</xsl:variable>
<xsl:variable name="GraphWidth">75e-2</xsl:variable>
<xsl:variable name="GraphHeight">75e-2</xsl:variable>
<xsl:variable name="Chart1Color">#aa20aa</xsl:variable>
<xsl:variable name="Chart2Color">#404000</xsl:variable>

	

<msxsl:script language="JScript" implements-prefix="dedek">

	
	function normalize_value(co, cim)
	{
		return Math.round(100*(co/cim));
	}


</msxsl:script>
	

<!-- nastaveni jazykovych popisku (labelu) -->


<xsl:variable name="label_item1">   <!-- 1. polozka tabulky-->
	<xsl:choose>	
		<xsl:when test="$lng='cz'">První množina</xsl:when>
		<xsl:when test="$lng='en'">First set</xsl:when>
		<xsl:otherwise>First set</xsl:otherwise>
	</xsl:choose>
</xsl:variable>

<xsl:variable name="label_item2">   <!-- 2. polozka tabulky-->
	<xsl:choose>	
		<xsl:when test="$lng='cz'">Druhá množina</xsl:when>
		<xsl:when test="$lng='en'">Second set</xsl:when>
		<xsl:otherwise>Second set</xsl:otherwise>
	</xsl:choose>
</xsl:variable>


	
	
<xsl:key name="key_ti_attribute" match="ti_attribute" use="@id" />
	

	
	
<!-- TEMPLATES-->	
	
	
	<xsl:template match="hyp_sdcf"> 
	
	  <xsl:if test="$FirstSetShow='true' or $SecondSetShow='true'">


		<xsl:variable name="id_base" select="@id" />
		
		<!-- cim se bude normalizovat (normalizacni faktor)-->
		<xsl:variable name="norm_factor_set1">
			<xsl:choose>
				<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="@sum1"/></xsl:when>
				<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="@max1"/></xsl:when>
				<xsl:otherwise>100</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="norm_factor_set2">
			<xsl:choose>
				<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="@sum2"/></xsl:when>
				<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="@max2"/></xsl:when>
				<xsl:otherwise>100</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
			
		<paragraph>
			<graph title="{$GraphTitle}" showlegend="{$LegendShow}" charttype="{$GraphType}" height="{$GraphHeight}" width="{$GraphWidth}" id="{@id}_sdgraph">
			
			<xsl:for-each select="key('key_ti_attribute',@attributes)">
				<xsl:call-template name="categories" />  <!-- vypsani kategorii-->
			</xsl:for-each>
			
			  <xsl:if test="$FirstSetShow='true'">	
				<xsl:element name="chart">
					<xsl:attribute name="id">chart1</xsl:attribute>				
					<xsl:attribute name="title"><xsl:value-of select="key('key_ti_attribute',@attributes)/@quant" /> - <xsl:value-of select="$label_item1"/></xsl:attribute>				
					<xsl:if test="$GraphType!='xl3DPie' and $GraphType!='xlPie'">
						<xsl:attribute name="color"><xsl:value-of select="$Chart1Color" /></xsl:attribute>				
					</xsl:if>
						<xsl:for-each select="r[position()=1]/c">
							<xsl:variable name="hodnota">
								<xsl:value-of select="dedek:normalize_value(number(@val),number($norm_factor_set1))"/>
								<xsl:if test="$ValuesType!='abs'">%</xsl:if>
							</xsl:variable>
							<value value="{$hodnota}" id="{$id_base}_val{position()}" />	
						</xsl:for-each>
				</xsl:element>
			  </xsl:if>			
			  
			  <xsl:if test="$SecondSetShow='true'">	
				<xsl:element name="chart">
					<xsl:attribute name="id">chart2</xsl:attribute>				
					<xsl:attribute name="title"><xsl:value-of select="key('key_ti_attribute',@attributes)/@quant" /> - <xsl:value-of select="$label_item2"/></xsl:attribute>				
					<xsl:if test="$GraphType!='xl3DPie' and $GraphType!='xlPie'">
						<xsl:attribute name="color"><xsl:value-of select="$Chart2Color" /></xsl:attribute>				
					</xsl:if>
						<xsl:for-each select="r[position()=2]/c">
							<xsl:variable name="hodnota">
								<xsl:value-of select="dedek:normalize_value(number(@val),number($norm_factor_set2))"/>
								<xsl:if test="$ValuesType!='abs'">%</xsl:if>
							</xsl:variable>
							<value value="{$hodnota}" id="{$id_base}_val{position()}" />	
						</xsl:for-each>
				</xsl:element>
			  </xsl:if>
							
			</graph>
		</paragraph>
	  
	  </xsl:if>						
	
	</xsl:template>
	
	
	
	<xsl:template name="categories" >  <!-- vypise kategorie atributu-->
		
			<categories id="{@id}_cats1">
				<xsl:variable name="id_base" select="@id" />
			
				<xsl:for-each select="ti_category" >	
					<category title="{@value}" id="{$id_base}_cat{position()}" />
				</xsl:for-each>
			</categories>
			
	</xsl:template>
      




</xsl:stylesheet>
