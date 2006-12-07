<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          
	
	
	
	<!-- nastaveni jazyka (defaultne cz) -->
	<xsl:variable name="lng">en</xsl:variable>
	

	
	
	
	<xsl:template match="hyp_sd4ft">

				<element_attributes>
		
					<xsl:apply-templates select="@*"/>

				</element_attributes>
				
	</xsl:template>

	
	
	
	
	<!-- vypise vsechny atributy (label + hodnota)-->
	<xsl:template match="@*">
	
				
		
			<!-- labely polozek-->
		<xsl:variable name="label">
			<xsl:choose>
			
				<!-- nezavisle na jazyce -->
				
					<!-- First set -->
					
				<xsl:when test="name()='conf1'">
					<xsl:text>Confidence 1: a/(a+b)</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='d_conf1'">
					<xsl:text>D-Confidence 1: a/(a+b+c)</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='e_conf1'">
					<xsl:text>E-Confidence 1: (a+d)/(a+b+c+d)</xsl:text>
				</xsl:when>
						
				<xsl:when test="name()='support1'">
					<xsl:text>Support 1: a/(a+b+c+d)</xsl:text>
				</xsl:when>
						
				<xsl:when test="name()='completeness1'">
					<xsl:text>Completeness 1: a/(a+c)</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='avg_diff1'">
					<xsl:text>Average difference 1: a(a+b+c+d)/((a+b)(a+c))- 1</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='low_bnd_imp1'">
					<xsl:text>Lower bound implication 1</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='up_bnd_imp1'">
					<xsl:text>Upper bound implication 1</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='low_bnd_dbl_imp1'">
					<xsl:text>Lower bound double implication 1</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='up_bnd_dbl_imp1'">
					<xsl:text>Upper bound double implication 1</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='low_bnd_eq1'">
					<xsl:text>Lower bound equivalence 1</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='up_bnd_eq1'">
					<xsl:text>Upper bound equivalence 1</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='fisher1'">
					<xsl:text>Fisher test 1</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='chi_sq1'">
					<xsl:text>Chi-square test 1</xsl:text>
				</xsl:when>
				
				 	<!-- Second set-->
				 	
				<xsl:when test="name()='conf2'">
					<xsl:text>Confidence 2: e/(e+f)</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='d_conf2'">
					<xsl:text>D-Confidence 2: e/(e+f+g)</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='e_conf2'">
					<xsl:text>E-Confidence 2: (e+h)/(e+f+g+h)</xsl:text>
				</xsl:when>
						
				<xsl:when test="name()='support2'">
					<xsl:text>Support 2: e/(e+f+g+h)</xsl:text>
				</xsl:when>
						
				<xsl:when test="name()='completeness2'">
					<xsl:text>Completeness 2: e/(e+g)</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='avg_diff2'">
					<xsl:text>Average difference 2: e(e+f+g+h)/((e+f)(e+g))- 1</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='low_bnd_imp2'">
					<xsl:text>Lower bound implication 2</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='up_bnd_imp2'">
					<xsl:text>Upper bound implication 2</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='low_bnd_dbl_imp2'">
					<xsl:text>Lower bound double implication 2</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='up_bnd_dbl_imp2'">
					<xsl:text>Upper bound double implication 2</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='low_bnd_eq2'">
					<xsl:text>Lower bound equivalence 2</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='up_bnd_eq2'">
					<xsl:text>Upper bound equivalence 2</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='fisher2'">
					<xsl:text>Fisher test 2</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='chi_sq2'">
					<xsl:text>Chi-square test 2</xsl:text>
				</xsl:when>
				
					<!-- Set differences-->
					
				
				
				<!-- cesky -->
				
				<xsl:when test="$lng='cz'">    
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Databáze</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Datová matice</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Jméno úlohy</xsl:text>
							</xsl:when>
							
							<!-- hodnoty kvantifikatoru - rozdily mezi mnozinami-->
							
							<xsl:when test="name()='dr_sum'">
								<xsl:text>D%-Sum (Součet rozdílů relativních frekvencí obou množin)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='df_conf'">
								<xsl:text>Df-Conf (Rozdíl hodnot Confidence)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='df_dfui'">
								<xsl:text>Df-DFUI (Rozdíl hodnot D-Confidence)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='df_fue'">
								<xsl:text>Df-FUE (Rozdíl hodnot E-Confidence)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='df_avg'">
								<xsl:text>Df-Avg (Rozdíl hodnot Average Difference)</xsl:text>
							</xsl:when>
							
						
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>
				</xsl:when>
				
				
				<!-- english-->
				
				<xsl:when test="$lng='en'">	
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Database</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Data matrix</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Task name</xsl:text>
							</xsl:when>
							
							<!-- quantifiers values - differences between set1 and set2-->
							
							<xsl:when test="name()='dr_sum'">
								<xsl:text>D%-Sum (Sum of differences of relative frequencies between sets)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='df_conf'">
								<xsl:text>Df-Conf (Difference of values of Confidence)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='df_dfui'">
								<xsl:text>Df-DFUI (Difference of values of D-Confidence)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='df_fue'">
								<xsl:text>Df-FUE (Difference of values of E-Confidence)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='df_avg'">
								<xsl:text>Df-Avg (Difference of values of Average Difference)</xsl:text>
							</xsl:when>
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>	
				</xsl:when>
				
				<!-- jinak se pouzije nazev XML atributu-->
				
				<xsl:otherwise>
					<xsl:value-of select="name()"/>
				</xsl:otherwise>
				
			</xsl:choose>
		</xsl:variable>
			<!-- end of: labely polozek-->

	
		<attribute name="{name()}" value="{.}" label="{$label}" />
				
	</xsl:template>
	
	
	



	<!-- naplni hodnotu cedentu-->
	<xsl:template match="@antecedent | @succedent | @condition | @set1 | @set2">
	
					<!-- zapise: <attribute name="{name()}" value=" label=""/>-->

    <!--label polozky-->
    <xsl:variable name="label">
      <xsl:choose>
        <xsl:when test="name()='antecedent'">
          <xsl:text>Antecedent</xsl:text>
        </xsl:when>
        <xsl:when test="name()='succedent'">
          <xsl:text>Succedent</xsl:text>
        </xsl:when>
        <xsl:when test="name()='condition'">
          <xsl:text>Condition</xsl:text>
        </xsl:when>
        <xsl:when test="name()='set1'">
          <xsl:text>First set</xsl:text>
        </xsl:when>
        <xsl:when test="name()='set2'">
          <xsl:text>Second set</xsl:text>
        </xsl:when>
        <xsl:otherwise>BooleanCedent</xsl:otherwise>
        <!--otherwise by nemelo nastat-->
      </xsl:choose>
    </xsl:variable>
    
    <xsl:element name="attribute">
      <xsl:attribute name="name">
        <xsl:value-of select="name()"/>
      </xsl:attribute>
      <xsl:attribute name="value">
        <!-- zapise hodnotu cedentu -->
        <xsl:apply-templates select="id(.)" mode="values"/>
      </xsl:attribute>
      <xsl:attribute name="label">
        <xsl:value-of select="$label"/>
      </xsl:attribute>
    </xsl:element>
    
	</xsl:template>
	



	<!-- literaly -> cedent -->
	<xsl:template match="ti_cedent" mode="values">		
    	<xsl:apply-templates select="ti_literal" mode="values"/>
	</xsl:template>
	

	<!-- preformatuje literal -->
	<xsl:template match="ti_literal" mode="values">		
		
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no"> &amp; </xsl:text>
		</xsl:if>

		
		<xsl:value-of select="@quant"/>
		<xsl:text disable-output-escaping="yes">(</xsl:text>
		<xsl:value-of select="@value"/>
		<xsl:text disable-output-escaping="yes">)</xsl:text>
	</xsl:template>
	






</xsl:stylesheet>
